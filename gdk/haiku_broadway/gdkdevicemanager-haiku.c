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

