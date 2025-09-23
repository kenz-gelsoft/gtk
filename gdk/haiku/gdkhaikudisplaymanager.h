/* gdkhaikudisplaymanager.h
 *
 * Copyright (C) 2005-2007  Imendio AB
 * Copyright 2010 Red Hat, Inc.
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

#ifndef __GDK_HAIKU_DISPLAY_MANAGER_H__
#define __GDK_HAIKU_DISPLAY_MANAGER_H__

#if !defined(__GDKQUARTZ_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkhaiku.h> can be included directly."
#endif

#include <gdk/gdk.h>

G_BEGIN_DECLS

#define GDK_TYPE_HAIKU_DISPLAY_MANAGER    (gdk_haiku_display_manager_get_type ())
#define GDK_HAIKU_DISPLAY_MANAGER(object) (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_DISPLAY_MANAGER, GdkHaikuDisplayManager))

#ifdef GDK_COMPILATION
typedef struct _GdkHaikuDisplayManager GdkHaikuDisplayManager;
#else
typedef GdkDisplayManager _GdkHaikuDisplayManager;
#endif
typedef struct _GdkDisplayManagerClass GdkHaikuDisplayManagerClass;


GDK_AVAILABLE_IN_ALL
GType gdk_haiku_display_manager_get_type (void);

G_END_DECLS

#endif /* __GDK_HAIKU_DISPLAY_MANAGER_H__ */
