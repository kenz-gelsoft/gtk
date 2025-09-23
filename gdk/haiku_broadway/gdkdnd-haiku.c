/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1999 Peter Mattis, Spencer Kimball and Josh MacDonald
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

#include "config.h"

#include "gdkdndprivate.h"

#include "gdkinternals.h"
#include "gdkproperty.h"
#include "gdkprivate-haiku.h"
#include "gdkinternals.h"
#include "gdkscreen-haiku.h"
#include "gdkdisplay-haiku.h"

#include <string.h>

#define GDK_TYPE_HAIKU_DRAG_CONTEXT              (gdk_haiku_drag_context_get_type ())
#define GDK_HAIKU_DRAG_CONTEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_DRAG_CONTEXT, GdkHaikuDragContext))
#define GDK_HAIKU_DRAG_CONTEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_HAIKU_DRAG_CONTEXT, GdkHaikuDragContextClass))
#define GDK_IS_HAIKU_DRAG_CONTEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_HAIKU_DRAG_CONTEXT))
#define GDK_IS_HAIKU_DRAG_CONTEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_HAIKU_DRAG_CONTEXT))
#define GDK_HAIKU_DRAG_CONTEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_HAIKU_DRAG_CONTEXT, GdkHaikuDragContextClass))

#ifdef GDK_COMPILATION
typedef struct _GdkHaikuDragContext GdkHaikuDragContext;
#else
typedef GdkDragContext GdkHaikuDragContext;
#endif
typedef struct _GdkHaikuDragContextClass GdkHaikuDragContextClass;

GType     gdk_haiku_drag_context_get_type (void);

struct _GdkHaikuDragContext {
  GdkDragContext context;
};

struct _GdkHaikuDragContextClass
{
  GdkDragContextClass parent_class;
};

static void gdk_haiku_drag_context_finalize (GObject *object);

static GList *contexts;

G_DEFINE_TYPE (GdkHaikuDragContext, gdk_haiku_drag_context, GDK_TYPE_DRAG_CONTEXT)

/* Drag Contexts */

static void
gdk_haiku_drag_context_finalize (GObject *object)
{
  GdkDragContext *context = GDK_DRAG_CONTEXT (object);

  contexts = g_list_remove (contexts, context);

  G_OBJECT_CLASS (gdk_haiku_drag_context_parent_class)->finalize (object);
}

static GdkWindow *
gdk_haiku_drag_context_find_window (GdkDragContext  *context,
				       GdkWindow       *drag_window,
				       GdkScreen       *screen,
				       gint             x_root,
				       gint             y_root,
				       GdkDragProtocol *protocol)
{
  g_return_val_if_fail (context != NULL, NULL);
  return NULL;
}

static gboolean
gdk_haiku_drag_context_drag_motion (GdkDragContext *context,
				       GdkWindow      *dest_window,
				       GdkDragProtocol protocol,
				       gint            x_root,
				       gint            y_root,
				       GdkDragAction   suggested_action,
				       GdkDragAction   possible_actions,
				       guint32         time)
{
  g_return_val_if_fail (context != NULL, FALSE);
  g_return_val_if_fail (dest_window == NULL || GDK_WINDOW_IS_BROADWAY (dest_window), FALSE);

  return FALSE;
}

static void
gdk_haiku_drag_context_drag_abort (GdkDragContext *context,
				      guint32         time)
{
  g_return_if_fail (context != NULL);
}

static void
gdk_haiku_drag_context_drag_drop (GdkDragContext *context,
				     guint32         time)
{
  g_return_if_fail (context != NULL);
}

/* Destination side */

void
_gdk_haiku_display_init_dnd (GdkDisplay *display)
{
}

static void
gdk_haiku_drag_context_drag_status (GdkDragContext   *context,
				       GdkDragAction     action,
				       guint32           time)
{
  g_return_if_fail (context != NULL);
}

static void
gdk_haiku_drag_context_drop_reply (GdkDragContext   *context,
				      gboolean          ok,
				      guint32           time)
{
  g_return_if_fail (context != NULL);
}

static void
gdk_haiku_drag_context_drop_finish (GdkDragContext   *context,
				       gboolean          success,
				       guint32           time)
{
  g_return_if_fail (context != NULL);
}

static gboolean
gdk_haiku_drag_context_drop_status (GdkDragContext *context)
{
  g_return_val_if_fail (context != NULL, FALSE);

  return FALSE;
}

static GdkAtom
gdk_haiku_drag_context_get_selection (GdkDragContext *context)
{
  g_return_val_if_fail (context != NULL, GDK_NONE);

  return GDK_NONE;
}

static void
gdk_haiku_drag_context_init (GdkHaikuDragContext *dragcontext)
{
  contexts = g_list_prepend (contexts, dragcontext);
}

static void
gdk_haiku_drag_context_class_init (GdkHaikuDragContextClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GdkDragContextClass *context_class = GDK_DRAG_CONTEXT_CLASS (klass);

  object_class->finalize = gdk_haiku_drag_context_finalize;

  context_class->find_window = gdk_haiku_drag_context_find_window;
  context_class->drag_status = gdk_haiku_drag_context_drag_status;
  context_class->drag_motion = gdk_haiku_drag_context_drag_motion;
  context_class->drag_abort = gdk_haiku_drag_context_drag_abort;
  context_class->drag_drop = gdk_haiku_drag_context_drag_drop;
  context_class->drop_reply = gdk_haiku_drag_context_drop_reply;
  context_class->drop_finish = gdk_haiku_drag_context_drop_finish;
  context_class->drop_status = gdk_haiku_drag_context_drop_status;
  context_class->get_selection = gdk_haiku_drag_context_get_selection;
}

GdkDragProtocol
_gdk_haiku_window_get_drag_protocol (GdkWindow *window,
					GdkWindow **target)
{
  return GDK_DRAG_PROTO_NONE;
}

void
_gdk_haiku_window_register_dnd (GdkWindow      *window)
{
}

GdkDragContext *
_gdk_haiku_window_drag_begin (GdkWindow *window,
				 GdkDevice *device,
				 GList     *targets,
                                 gint       x_root,
                                 gint       y_root)
{
  GdkDragContext *new_context;

  g_return_val_if_fail (window != NULL, NULL);
  g_return_val_if_fail (GDK_WINDOW_IS_BROADWAY (window), NULL);

  new_context = g_object_new (GDK_TYPE_HAIKU_DRAG_CONTEXT,
			      NULL);
  new_context->display = gdk_window_get_display (window);

  return new_context;
}
