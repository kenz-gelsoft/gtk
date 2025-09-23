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

#ifndef __GDK_HAIKU_DEVICE_CORE_H__
#define __GDK_HAIKU_DEVICE_CORE_H__

#if !defined(__GDKQUARTZ_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkhaiku.h> can be included directly."
#endif

#include <gdk/gdk.h>

G_BEGIN_DECLS

#define GDK_TYPE_HAIKU_DEVICE_CORE         (gdk_haiku_device_core_get_type ())
#define GDK_HAIKU_DEVICE_CORE(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GDK_TYPE_HAIKU_DEVICE_CORE, GdkHaikuDeviceCore))
#define GDK_HAIKU_DEVICE_CORE_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST ((c), GDK_TYPE_HAIKU_DEVICE_CORE, GdkHaikuDeviceCoreClass))
#define GDK_IS_HAIKU_DEVICE_CORE(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GDK_TYPE_HAIKU_DEVICE_CORE))
#define GDK_IS_HAIKU_DEVICE_CORE_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE ((c), GDK_TYPE_HAIKU_DEVICE_CORE))
#define GDK_HAIKU_DEVICE_CORE_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GDK_TYPE_HAIKU_DEVICE_CORE, GdkHaikuDeviceCoreClass))

typedef struct _GdkHaikuDeviceCore GdkHaikuDeviceCore;
typedef struct _GdkHaikuDeviceCoreClass GdkHaikuDeviceCoreClass;

GDK_AVAILABLE_IN_ALL
GType gdk_haiku_device_core_get_type (void) G_GNUC_CONST;

G_END_DECLS

#endif /* __GDK_HAIKU_DEVICE_CORE_H__ */
