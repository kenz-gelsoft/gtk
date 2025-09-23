#ifndef __HAIKU_H__
#define __HAIKU_H__

#include <glib.h>
#include <gio/gio.h>
#include "haiku-protocol.h"
#include "haiku-buffer.h"

typedef struct HaikuOutput HaikuOutput;

typedef enum {
  HAIKU_WS_CONTINUATION = 0,
  HAIKU_WS_TEXT = 1,
  HAIKU_WS_BINARY = 2,
  HAIKU_WS_CNX_CLOSE = 8,
  HAIKU_WS_CNX_PING = 9,
  HAIKU_WS_CNX_PONG = 0xa
} HaikuWSOpCode;

HaikuOutput *haiku_output_new             (GOutputStream  *out,
						 guint32         serial);
void            haiku_output_free            (HaikuOutput *output);
int             haiku_output_flush           (HaikuOutput *output);
int             haiku_output_has_error       (HaikuOutput *output);
void            haiku_output_set_next_serial (HaikuOutput *output,
						 guint32         serial);
guint32         haiku_output_get_next_serial (HaikuOutput *output);
void            haiku_output_new_surface     (HaikuOutput *output,
						 int             id,
						 int             x,
						 int             y,
						 int             w,
						 int             h,
						 gboolean        is_temp);
void            haiku_output_disconnected    (HaikuOutput *output);
void            haiku_output_show_surface    (HaikuOutput *output,
						 int             id);
void            haiku_output_hide_surface    (HaikuOutput *output,
						 int             id);
void            haiku_output_raise_surface   (HaikuOutput *output,
                                                 int             id);
void            haiku_output_lower_surface   (HaikuOutput *output,
                                                 int             id);
void            haiku_output_destroy_surface (HaikuOutput *output,
						 int             id);
void            haiku_output_move_resize_surface (HaikuOutput *output,
						     int             id,
						     gboolean        has_pos,
						     int             x,
						     int             y,
						     gboolean        has_size,
						     int             w,
						     int             h);
void            haiku_output_set_transient_for (HaikuOutput *output,
						   int             id,
						   int             parent_id);
void            haiku_output_put_buffer      (HaikuOutput *output,
						 int             id,
                                                 HaikuBuffer *prev_buffer,
                                                 HaikuBuffer *buffer);
void            haiku_output_grab_pointer    (HaikuOutput *output,
						 int id,
						 gboolean owner_event);
guint32         haiku_output_ungrab_pointer  (HaikuOutput *output);
void            haiku_output_pong            (HaikuOutput *output);
void            haiku_output_set_show_keyboard (HaikuOutput *output,
                                                   gboolean show);

#endif /* __HAIKU_H__ */
