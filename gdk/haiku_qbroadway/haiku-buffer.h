#ifndef __HAIKU_BUFFER__
#define __HAIKU_BUFFER__

#include "haiku-protocol.h"
#include <glib-object.h>

typedef struct _HaikuBuffer HaikuBuffer;

HaikuBuffer *haiku_buffer_create     (int             width,
                                            int             height,
                                            guint8         *data,
                                            int             stride);
void            haiku_buffer_destroy    (HaikuBuffer *buffer);
void            haiku_buffer_encode     (HaikuBuffer *buffer,
                                            HaikuBuffer *prev,
                                            GString        *dest);
int             haiku_buffer_get_width  (HaikuBuffer *buffer);
int             haiku_buffer_get_height (HaikuBuffer *buffer);

#endif /* __HAIKU_BUFFER__ */
