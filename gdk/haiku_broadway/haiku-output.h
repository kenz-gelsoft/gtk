#ifndef __BROADWAY_H__
#define __BROADWAY_H__

#include <glib.h>
#include <gio/gio.h>
#include "haiku-protocol.h"
#include "haiku-buffer.h"

typedef struct BroadwayOutput BroadwayOutput;

typedef enum {
  BROADWAY_WS_CONTINUATION = 0,
  BROADWAY_WS_TEXT = 1,
  BROADWAY_WS_BINARY = 2,
  BROADWAY_WS_CNX_CLOSE = 8,
  BROADWAY_WS_CNX_PING = 9,
  BROADWAY_WS_CNX_PONG = 0xa
} BroadwayWSOpCode;

BroadwayOutput *haiku_output_new             (GOutputStream  *out,
						 guint32         serial);
void            haiku_output_free            (BroadwayOutput *output);
int             haiku_output_flush           (BroadwayOutput *output);
int             haiku_output_has_error       (BroadwayOutput *output);
void            haiku_output_set_next_serial (BroadwayOutput *output,
						 guint32         serial);
guint32         haiku_output_get_next_serial (BroadwayOutput *output);
void            haiku_output_new_surface     (BroadwayOutput *output,
						 int             id,
						 int             x,
						 int             y,
						 int             w,
						 int             h,
						 gboolean        is_temp);
void            haiku_output_disconnected    (BroadwayOutput *output);
void            haiku_output_show_surface    (BroadwayOutput *output,
						 int             id);
void            haiku_output_hide_surface    (BroadwayOutput *output,
						 int             id);
void            haiku_output_raise_surface   (BroadwayOutput *output,
                                                 int             id);
void            haiku_output_lower_surface   (BroadwayOutput *output,
                                                 int             id);
void            haiku_output_destroy_surface (BroadwayOutput *output,
						 int             id);
void            haiku_output_move_resize_surface (BroadwayOutput *output,
						     int             id,
						     gboolean        has_pos,
						     int             x,
						     int             y,
						     gboolean        has_size,
						     int             w,
						     int             h);
void            haiku_output_set_transient_for (BroadwayOutput *output,
						   int             id,
						   int             parent_id);
void            haiku_output_put_buffer      (BroadwayOutput *output,
						 int             id,
                                                 BroadwayBuffer *prev_buffer,
                                                 BroadwayBuffer *buffer);
void            haiku_output_grab_pointer    (BroadwayOutput *output,
						 int id,
						 gboolean owner_event);
guint32         haiku_output_ungrab_pointer  (BroadwayOutput *output);
void            haiku_output_pong            (BroadwayOutput *output);
void            haiku_output_set_show_keyboard (BroadwayOutput *output,
                                                   gboolean show);

#endif /* __BROADWAY_H__ */
