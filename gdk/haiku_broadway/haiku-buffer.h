#ifndef __BROADWAY_BUFFER__
#define __BROADWAY_BUFFER__

#include "haiku-protocol.h"
#include <glib-object.h>

typedef struct _BroadwayBuffer BroadwayBuffer;

BroadwayBuffer *haiku_buffer_create     (int             width,
                                            int             height,
                                            guint8         *data,
                                            int             stride);
void            haiku_buffer_destroy    (BroadwayBuffer *buffer);
void            haiku_buffer_encode     (BroadwayBuffer *buffer,
                                            BroadwayBuffer *prev,
                                            GString        *dest);
int             haiku_buffer_get_width  (BroadwayBuffer *buffer);
int             haiku_buffer_get_height (BroadwayBuffer *buffer);

#endif /* __BROADWAY_BUFFER__ */
