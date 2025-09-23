#ifndef __HAIKU_SERVER__
#define __HAIKU_SERVER__

#include "haiku-protocol.h"
#include <glib-object.h>
#include <cairo.h>

void haiku_events_got_input (HaikuInputMsg *message,
				gint32 client_id);

typedef struct _HaikuServer HaikuServer;
typedef struct _HaikuServerClass HaikuServerClass;

#define HAIKU_TYPE_SERVER              (haiku_server_get_type())
#define HAIKU_SERVER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), HAIKU_TYPE_SERVER, HaikuServer))
#define HAIKU_SERVER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), HAIKU_TYPE_SERVER, HaikuServerClass))
#define HAIKU_IS_SERVER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), HAIKU_TYPE_SERVER))
#define HAIKU_IS_SERVER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), HAIKU_TYPE_SERVER))
#define HAIKU_SERVER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), HAIKU_TYPE_SERVER, HaikuServerClass))


HaikuServer     *haiku_server_new                      (char             *address,
							      int               port,
                                                              const char       *ssl_cert,
                                                              const char       *ssl_key,
							      GError          **error);
HaikuServer     *haiku_server_on_unix_socket_new       (char             *address,
							      GError          **error);
gboolean            haiku_server_has_client               (HaikuServer   *server);
void                haiku_server_flush                    (HaikuServer   *server);
void                haiku_server_sync                     (HaikuServer   *server);
void                haiku_server_get_screen_size          (HaikuServer   *server,
							      guint32          *width,
							      guint32          *height);
guint32             haiku_server_get_next_serial          (HaikuServer   *server);
guint32             haiku_server_get_last_seen_time       (HaikuServer   *server);
gboolean            haiku_server_lookahead_event          (HaikuServer   *server,
							      const char       *types);
void                haiku_server_query_mouse              (HaikuServer   *server,
							      guint32          *toplevel,
							      gint32           *root_x,
							      gint32           *root_y,
							      guint32          *mask);
guint32             haiku_server_grab_pointer             (HaikuServer   *server,
							      gint              client_id,
							      gint              id,
							      gboolean          owner_events,
							      guint32           event_mask,
							      guint32           time_);
guint32             haiku_server_ungrab_pointer           (HaikuServer   *server,
							      guint32           time_);
gint32              haiku_server_get_mouse_toplevel       (HaikuServer   *server);
void                haiku_server_set_show_keyboard        (HaikuServer   *server,
                                                              gboolean          show);
guint32             haiku_server_new_window               (HaikuServer   *server,
							      int               x,
							      int               y,
							      int               width,
							      int               height,
							      gboolean          is_temp);
void                haiku_server_destroy_window           (HaikuServer   *server,
							      gint              id);
gboolean            haiku_server_window_show              (HaikuServer   *server,
							      gint              id);
gboolean            haiku_server_window_hide              (HaikuServer   *server,
							      gint              id);
void                haiku_server_window_raise             (HaikuServer   *server,
							      gint              id);
void                haiku_server_window_lower             (HaikuServer   *server,
							      gint              id);
void                haiku_server_window_set_transient_for (HaikuServer   *server,
							      gint              id,
							      gint              parent);
gboolean            haiku_server_window_translate         (HaikuServer   *server,
							      gint              id,
							      cairo_region_t   *area,
							      gint              dx,
							      gint              dy);
cairo_surface_t   * haiku_server_create_surface           (int               width,
							      int               height);
void                haiku_server_window_update            (HaikuServer   *server,
							      gint              id,
							      cairo_surface_t  *surface);
gboolean            haiku_server_window_move_resize       (HaikuServer   *server,
							      gint              id,
							      gboolean          with_move,
							      int               x,
							      int               y,
							      int               width,
							      int               height);
void                haiku_server_focus_window             (HaikuServer   *server,
                                                              gint              new_focused_window);
cairo_surface_t * haiku_server_open_surface (HaikuServer *server,
						guint32 id,
						char *name,
						int width,
						int height);
void                haiku_server_window_set_modal_hint (HaikuServer   *server,
							   gint              id,
							   gboolean          modal_hint);

#endif /* __HAIKU_SERVER__ */
