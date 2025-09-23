/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
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

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/. 
 */

#ifndef __GDK_HAIKU_CURSOR_H__
#define __GDK_HAIKU_CURSOR_H__

#if !defined (__GDKHAIKU_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkhaiku.h> can be included directly."
#endif

#include <gdk/gdk.h>

G_BEGIN_DECLS

#define GDK_TYPE_HAIKU_CURSOR              (gdk_haiku_cursor_get_type ())
#define GDK_HAIKU_CURSOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_CURSOR, GdkHaikuCursor))
#define GDK_HAIKU_CURSOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_HAIKU_CURSOR, GdkHaikuCursorClass))
#define GDK_IS_HAIKU_CURSOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_HAIKU_CURSOR))
#define GDK_IS_HAIKU_CURSOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_HAIKU_CURSOR))
#define GDK_HAIKU_CURSOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_HAIKU_CURSOR, GdkHaikuCursorClass))

#ifdef GDK_COMPILATION
typedef struct _GdkHaikuCursor GdkHaikuCursor;
#else
typedef GdkCursor GdkHaikuCursor;
#endif
typedef struct _GdkHaikuCursorClass GdkHaikuCursorClass;

GDK_AVAILABLE_IN_ALL
GType    gdk_haiku_cursor_get_type          (void);

G_END_DECLS

#endif /* __GDK_HAIKU_CURSOR_H__ */
