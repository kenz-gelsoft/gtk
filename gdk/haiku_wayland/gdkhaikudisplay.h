/* GDK - The GIMP Drawing Kit
 * Copyright (C) 2013 Jan Arne Petersen
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

#ifndef __GDK_HAIKU_DISPLAY_H__
#define __GDK_HAIKU_DISPLAY_H__

#if !defined (__GDKWAYLAND_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkhaiku.h> can be included directly."
#endif

#include <gdk/gdk.h>

#include <haiku-client.h>

G_BEGIN_DECLS

#ifdef GDK_COMPILATION
typedef struct _GdkHaikuDisplay GdkHaikuDisplay;
#else
typedef GdkDisplay GdkHaikuDisplay;
#endif
typedef struct _GdkHaikuDisplayClass GdkHaikuDisplayClass;

#define GDK_TYPE_HAIKU_DISPLAY              (gdk_haiku_display_get_type())
#define GDK_HAIKU_DISPLAY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_DISPLAY, GdkHaikuDisplay))
#define GDK_HAIKU_DISPLAY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_HAIKU_DISPLAY, GdkHaikuDisplayClass))
#define GDK_IS_HAIKU_DISPLAY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_HAIKU_DISPLAY))
#define GDK_IS_HAIKU_DISPLAY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_HAIKU_DISPLAY))
#define GDK_HAIKU_DISPLAY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_HAIKU_DISPLAY, GdkHaikuDisplayClass))

GDK_AVAILABLE_IN_ALL
GType                   gdk_haiku_display_get_type            (void);

GDK_AVAILABLE_IN_ALL
struct wl_display      *gdk_haiku_display_get_wl_display      (GdkDisplay *display);
GDK_AVAILABLE_IN_ALL
struct wl_compositor   *gdk_haiku_display_get_wl_compositor   (GdkDisplay *display);
GDK_AVAILABLE_IN_3_10
void                    gdk_haiku_display_set_cursor_theme    (GdkDisplay  *display,
                                                                 const gchar *theme,
                                                                 gint         size);
GDK_AVAILABLE_IN_3_22
void                    gdk_haiku_display_set_startup_notification_id (GdkDisplay *display,
                                                                         const char *startup_id);

GDK_AVAILABLE_IN_3_22
gboolean                gdk_haiku_display_prefers_ssd         (GdkDisplay *display);

GDK_AVAILABLE_IN_3_22
gboolean                gdk_haiku_display_query_registry      (GdkDisplay  *display,
								 const gchar *global);

G_END_DECLS

#endif /* __GDK_HAIKU_DISPLAY_H__ */
