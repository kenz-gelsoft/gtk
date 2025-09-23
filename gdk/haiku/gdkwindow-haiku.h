/* gdkdrawable-haiku.h
 *
 * Copyright (C) 2005 Imendio AB
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

#ifndef __GDK_WINDOW_QUARTZ_H__
#define __GDK_WINDOW_QUARTZ_H__

#import <gdk/quartz/GdkHaikuView.h>
#import <gdk/quartz/GdkHaikuNSWindow.h>
#include "gdk/gdkwindowimpl.h"

G_BEGIN_DECLS

/* Window implementation for Quartz
 */

typedef struct _GdkWindowImplHaiku GdkWindowImplHaiku;
typedef struct _GdkWindowImplHaikuClass GdkWindowImplHaikuClass;

#define GDK_TYPE_WINDOW_IMPL_QUARTZ              (_gdk_window_impl_haiku_get_type ())
#define GDK_WINDOW_IMPL_QUARTZ(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_WINDOW_IMPL_QUARTZ, GdkWindowImplHaiku))
#define GDK_WINDOW_IMPL_QUARTZ_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_WINDOW_IMPL_QUARTZ, GdkWindowImplHaikuClass))
#define GDK_IS_WINDOW_IMPL_QUARTZ(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_WINDOW_IMPL_QUARTZ))
#define GDK_IS_WINDOW_IMPL_QUARTZ_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_WINDOW_IMPL_QUARTZ))
#define GDK_WINDOW_IMPL_QUARTZ_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_WINDOW_IMPL_QUARTZ, GdkWindowImplHaikuClass))

struct _GdkWindowImplHaiku
{
  GdkWindowImpl parent_instance;

  GdkWindow *wrapper;

  NSWindow *toplevel;
  NSTrackingRectTag tracking_rect;
  GdkHaikuView *view;

  GdkWindowTypeHint type_hint;

  gint in_paint_rect_count;

  GdkWindow *transient_for;

  /* Sorted by z-order */
  GList *sorted_children;

  cairo_region_t *needs_display_region;

  cairo_surface_t *cairo_surface;

  gint shadow_top;

  gint shadow_max;

  gboolean use_cg_context;
  GSList frame_link;
  gint pending_frame_counter;
};
 
struct _GdkWindowImplHaikuClass 
{
  GdkWindowImplClass parent_class;

  CGContextRef  (* get_context)     (GdkWindowImplHaiku *window,
                                     gboolean             antialias);
  void          (* release_context) (GdkWindowImplHaiku *window,
                                     CGContextRef         cg_context);
};

GType _gdk_window_impl_haiku_get_type (void);

CGContextRef gdk_haiku_window_get_context     (GdkWindowImplHaiku *window,
                                                gboolean             antialias);
void         gdk_haiku_window_release_context (GdkWindowImplHaiku *window,
                                                CGContextRef         context);

/* Root window implementation for Quartz
 */

typedef struct _GdkRootWindowImplHaiku GdkRootWindowImplHaiku;
typedef struct _GdkRootWindowImplHaikuClass GdkRootWindowImplHaikuClass;

#define GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ              (_gdk_root_window_impl_haiku_get_type ())
#define GDK_ROOT_WINDOW_IMPL_QUARTZ(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ, GdkRootWindowImplHaiku))
#define GDK_ROOT_WINDOW_IMPL_QUARTZ_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ, GdkRootWindowImplHaikuClass))
#define GDK_IS_ROOT_WINDOW_IMPL_QUARTZ(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ))
#define GDK_IS_ROOT_WINDOW_IMPL_QUARTZ_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ))
#define GDK_ROOT_WINDOW_IMPL_QUARTZ_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_ROOT_WINDOW_IMPL_QUARTZ, GdkRootWindowImplHaikuClass))

struct _GdkRootWindowImplHaiku
{
  GdkWindowImplHaiku parent_instance;
  CGContextRef cg_context;
  GList* cg_layers;
};
 
struct _GdkRootWindowImplHaikuClass 
{
  GdkWindowImplHaikuClass parent_class;
};

GType _gdk_root_window_impl_haiku_get_type (void);

G_END_DECLS

#endif /* __GDK_WINDOW_QUARTZ_H__ */
