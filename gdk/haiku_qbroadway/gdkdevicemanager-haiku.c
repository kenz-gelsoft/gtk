/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2009 Carlos Garnacho <carlosg@gnome.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include "gdkdevicemanager-haiku.h"

#include "gdktypes.h"
#include "gdkdevicemanager.h"
#include "gdkdevice-haiku.h"
#include "gdkkeysyms.h"
#include "gdkprivate-haiku.h"
#include "gdkseatdefaultprivate.h"

#define HAS_FOCUS(toplevel)                           \
  ((toplevel)->has_focus || (toplevel)->has_pointer_focus)

static void    gdk_haiku_device_manager_finalize    (GObject *object);
static void    gdk_haiku_device_manager_constructed (GObject *object);

static GList * gdk_haiku_device_manager_list_devices (GdkDeviceManager *device_manager,
							 GdkDeviceType     type);
static GdkDevice * gdk_haiku_device_manager_get_client_pointer (GdkDeviceManager *device_manager);

G_DEFINE_TYPE (GdkHaikuDeviceManager, gdk_haiku_device_manager, GDK_TYPE_DEVICE_MANAGER)

static void
gdk_haiku_device_manager_class_init (GdkHaikuDeviceManagerClass *klass)
{
  GdkDeviceManagerClass *device_manager_class = GDK_DEVICE_MANAGER_CLASS (klass);
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->finalize = gdk_haiku_device_manager_finalize;
  object_class->constructed = gdk_haiku_device_manager_constructed;
  device_manager_class->list_devices = gdk_haiku_device_manager_list_devices;
  device_manager_class->get_client_pointer = gdk_haiku_device_manager_get_client_pointer;
}

static GdkDevice *
create_core_pointer (GdkDeviceManager *device_manager,
                     GdkDisplay       *display)
{
  return g_object_new (GDK_TYPE_HAIKU_DEVICE,
                       "name", "Core Pointer",
                       "type", GDK_DEVICE_TYPE_MASTER,
                       "input-source", GDK_SOURCE_MOUSE,
                       "input-mode", GDK_MODE_SCREEN,
                       "has-cursor", TRUE,
                       "display", display,
                       "device-manager", device_manager,
                       NULL);
}

static GdkDevice *
create_core_keyboard (GdkDeviceManager *device_manager,
                      GdkDisplay       *display)
{
  return g_object_new (GDK_TYPE_HAIKU_DEVICE,
                       "name", "Core Keyboard",
                       "type", GDK_DEVICE_TYPE_MASTER,
                       "input-source", GDK_SOURCE_KEYBOARD,
                       "input-mode", GDK_MODE_SCREEN,
                       "has-cursor", FALSE,
                       "display", display,
                       "device-manager", device_manager,
                       NULL);
}

static GdkDevice *
create_touchscreen (GdkDeviceManager *device_manager,
                    GdkDisplay       *display)
{
  return g_object_new (GDK_TYPE_HAIKU_DEVICE,
                       "name", "Touchscreen",
                       "type", GDK_DEVICE_TYPE_SLAVE,
                       "input-source", GDK_SOURCE_TOUCHSCREEN,
                       "input-mode", GDK_MODE_SCREEN,
                       "has-cursor", FALSE,
                       "display", display,
                       "device-manager", device_manager,
                       NULL);
}

static void
gdk_haiku_device_manager_init (GdkHaikuDeviceManager *device_manager)
{
}

static void
gdk_haiku_device_manager_finalize (GObject *object)
{
  GdkHaikuDeviceManager *device_manager;

  device_manager = GDK_HAIKU_DEVICE_MANAGER (object);

  g_object_unref (device_manager->core_pointer);
  g_object_unref (device_manager->core_keyboard);
  g_object_unref (device_manager->touchscreen);

  G_OBJECT_CLASS (gdk_haiku_device_manager_parent_class)->finalize (object);
}

static void
gdk_haiku_device_manager_constructed (GObject *object)
{
  GdkHaikuDeviceManager *device_manager;
  GdkDisplay *display;
  GdkSeat *seat;

  device_manager = GDK_HAIKU_DEVICE_MANAGER (object);
  display = gdk_device_manager_get_display (GDK_DEVICE_MANAGER (object));
  device_manager->core_pointer = create_core_pointer (GDK_DEVICE_MANAGER (device_manager), display);
  device_manager->core_keyboard = create_core_keyboard (GDK_DEVICE_MANAGER (device_manager), display);
  device_manager->touchscreen = create_touchscreen (GDK_DEVICE_MANAGER (device_manager), display);

  _gdk_device_set_associated_device (device_manager->core_pointer, device_manager->core_keyboard);
  _gdk_device_set_associated_device (device_manager->core_keyboard, device_manager->core_pointer);
  _gdk_device_set_associated_device (device_manager->touchscreen, device_manager->core_pointer);
  _gdk_device_add_slave (device_manager->core_pointer, device_manager->touchscreen);

  seat = gdk_seat_default_new_for_master_pair (device_manager->core_pointer,
                                               device_manager->core_keyboard);
  gdk_display_add_seat (display, seat);
  gdk_seat_default_add_slave (GDK_SEAT_DEFAULT (seat), device_manager->touchscreen);
  g_object_unref (seat);
}


static GList *
gdk_haiku_device_manager_list_devices (GdkDeviceManager *device_manager,
					  GdkDeviceType     type)
{
  GdkHaikuDeviceManager *haiku_device_manager = (GdkHaikuDeviceManager *) device_manager;
  GList *devices = NULL;

  if (type == GDK_DEVICE_TYPE_MASTER)
    {
      devices = g_list_prepend (devices, haiku_device_manager->core_keyboard);
      devices = g_list_prepend (devices, haiku_device_manager->core_pointer);
    }

  if (type == GDK_DEVICE_TYPE_SLAVE)
    {
      devices = g_list_prepend (devices, haiku_device_manager->touchscreen);
    }

  return devices;
}

static GdkDevice *
gdk_haiku_device_manager_get_client_pointer (GdkDeviceManager *device_manager)
{
  GdkHaikuDeviceManager *haiku_device_manager = (GdkHaikuDeviceManager *) device_manager;

  return haiku_device_manager->core_pointer;
}

GdkDeviceManager *
_gdk_haiku_device_manager_new (GdkDisplay *display)
{
  return g_object_new (GDK_TYPE_HAIKU_DEVICE_MANAGER,
		       "display", display,
		       NULL);
}
