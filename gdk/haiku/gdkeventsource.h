/* gdkeventsource.h
 *
 * Copyright (C) 2015 Christian Hergert <christian@hergert.me>
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
 *
 * Authors:
 *   Christian Hergert <christian@hergert.me>
 */

#ifndef GDK_DISPLAY_LINK_SOURCE_H
#define GDK_DISPLAY_LINK_SOURCE_H

#include <glib.h>

//#include <QuartzCore/QuartzCore.h>

G_BEGIN_DECLS

typedef struct
{
  GSource          source;

//  CVDisplayLinkRef display_link;
  gint64           refresh_interval;

  volatile gint64  presentation_time;
  volatile guint   needs_dispatch;
} GdkHaikuEventSource;

GSource *gdk_haiku_event_source_new     (void);
void     gdk_haiku_event_source_pause   (GdkHaikuEventSource *source);
void     gdk_haiku_event_source_unpause (GdkHaikuEventSource *source);

G_END_DECLS

#endif /* GDK_DISPLAY_LINK_SOURCE_H */
