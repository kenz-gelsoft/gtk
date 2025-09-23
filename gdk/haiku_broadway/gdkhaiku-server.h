#ifndef __GDK_HAIKU_SERVER__
#define __GDK_HAIKU_SERVER__

#include <gdk/gdktypes.h>
#include "haiku-protocol.h"

typedef struct _GdkHaikuServer GdkHaikuServer;
typedef struct _GdkHaikuServerClass GdkHaikuServerClass;

#define GDK_TYPE_HAIKU_SERVER              (gdk_haiku_server_get_type())
#define GDK_HAIKU_SERVER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_SERVER, GdkHaikuServer))
#define GDK_HAIKU_SERVER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_HAIKU_SERVER, GdkHaikuServerClass))
#define GDK_IS_HAIKU_SERVER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_HAIKU_SERVER))
#define GDK_IS_HAIKU_SERVER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_HAIKU_SERVER))
#define GDK_HAIKU_SERVER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_HAIKU_SERVER, GdkHaikuServerClass))

GdkHaikuServer *_gdk_haiku_server_new                      (const char         *display,
								  GError            **error);
void               _gdk_haiku_server_flush                    (GdkHaikuServer  *server);
void               _gdk_haiku_server_sync                     (GdkHaikuServer  *server);
gulong             _gdk_haiku_server_get_next_serial          (GdkHaikuServer  *server);
guint32            _gdk_haiku_server_get_last_seen_time       (GdkHaikuServer  *server);
gboolean           _gdk_haiku_server_lookahead_event          (GdkHaikuServer  *server,
								  const char         *types);
void               _gdk_haiku_server_query_mouse              (GdkHaikuServer  *server,
								  guint32            *toplevel,
								  gint32             *root_x,
								  gint32             *root_y,
								  guint32            *mask);
GdkGrabStatus      _gdk_haiku_server_grab_pointer             (GdkHaikuServer  *server,
								  gint                id,
								  gboolean            owner_events,
								  guint32             event_mask,
								  guint32             time_);
guint32            _gdk_haiku_server_ungrab_pointer           (GdkHaikuServer  *server,
								  guint32             time_);
gint32             _gdk_haiku_server_get_mouse_toplevel       (GdkHaikuServer  *server);
guint32            _gdk_haiku_server_new_window               (GdkHaikuServer  *server,
								  int                 x,
								  int                 y,
								  int                 width,
								  int                 height,
								  gboolean            is_temp);
void               _gdk_haiku_server_destroy_window           (GdkHaikuServer  *server,
								  gint                id);
gboolean           _gdk_haiku_server_window_show              (GdkHaikuServer  *server,
								  gint                id);
gboolean           _gdk_haiku_server_window_hide              (GdkHaikuServer  *server,
								  gint                id);
void               _gdk_haiku_server_window_focus             (GdkHaikuServer  *server,
								  gint                id);
void               _gdk_haiku_server_window_set_transient_for (GdkHaikuServer  *server,
								  gint                id,
								  gint                parent);
void               _gdk_haiku_server_set_show_keyboard        (GdkHaikuServer  *server,
								  gboolean            show_keyboard);
gboolean           _gdk_haiku_server_window_translate         (GdkHaikuServer  *server,
								  gint                id,
								  cairo_region_t     *area,
								  gint                dx,
								  gint                dy);
cairo_surface_t   *_gdk_haiku_server_create_surface           (int                 width,
								  int                 height);
void               _gdk_haiku_server_window_update            (GdkHaikuServer  *server,
								  gint                id,
								  cairo_surface_t    *surface);
gboolean           _gdk_haiku_server_window_move_resize       (GdkHaikuServer  *server,
								  gint                id,
								  gboolean            with_move,
								  int                 x,
								  int                 y,
								  int                 width,
								  int                 height);
void               _gdk_haiku_server_window_set_modal_hint    (GdkHaikuServer  *server,
								  gint                id,
								  gboolean            modal_hint);

#endif /* __GDK_HAIKU_SERVER__ */
