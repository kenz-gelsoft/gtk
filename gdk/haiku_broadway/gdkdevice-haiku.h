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

#ifndef __GDK_DEVICE_BROADWAY_H__
#define __GDK_DEVICE_BROADWAY_H__

#include <gdk/gdkdeviceprivate.h>

G_BEGIN_DECLS

#define GDK_TYPE_HAIKU_DEVICE         (gdk_haiku_device_get_type ())
#define GDK_HAIKU_DEVICE(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_HAIKU_DEVICE, GdkHaikuDevice))
#define GDK_HAIKU_DEVICE_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GDK_TYPE_HAIKU_DEVICE, GdkHaikuDeviceClass))
#define GDK_IS_HAIKU_DEVICE(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_HAIKU_DEVICE))
#define GDK_IS_HAIKU_DEVICE_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GDK_TYPE_HAIKU_DEVICE))
#define GDK_HAIKU_DEVICE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDK_TYPE_HAIKU_DEVICE, GdkHaikuDeviceClass))

typedef struct _GdkHaikuDevice GdkHaikuDevice;
typedef struct _GdkHaikuDeviceClass GdkHaikuDeviceClass;

struct _GdkHaikuDevice
{
  GdkDevice parent_instance;
};

struct _GdkHaikuDeviceClass
{
  GdkDeviceClass parent_class;
};

G_GNUC_INTERNAL
GType gdk_haiku_device_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __GDK_DEVICE_BROADWAY_H__ */
