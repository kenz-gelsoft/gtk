/* gdkhaikukeyd.h
 *
 * Copyright (C) 2005  Imendio AB
 * Copyright (C) 2010  Kristian Rietveld  <kris@gtk.org>
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

#ifndef __GDK_HAIKU_KEYS_H__
#define __GDK_HAIKU_KEYS_H__

#if !defined (__GDKHAIKU_H_INSIDE__) && !defined (GDK_COMPILATION)
#error "Only <gdk/gdkhaiku.h> can be included directly."
#endif

#include <gdk/gdk.h>

G_BEGIN_DECLS

#define GDK_TYPE_HAIKU_KEYMAP              (gdk_haiku_keymap_get_type ())
#define GDK_HAIKU_KEYMAP(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), GDK_TYPE_HAIKU_KEYMAP, GdkHaikuKeymap))
#define GDK_HAIKU_KEYMAP_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GDK_TYPE_HAIKU_KEYMAP, GdkHaikuKeymapClass))
#define GDK_IS_HAIKU_KEYMAP(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDK_TYPE_HAIKU_KEYMAP))
#define GDK_IS_HAIKU_KEYMAP_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GDK_TYPE_HAIKU_KEYMAP))
#define GDK_HAIKU_KEYMAP_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GDK_TYPE_HAIKU_KEYMAP, GdkHaikuKeymapClass))

#ifdef GDK_COMPILATION
typedef struct _GdkHaikuKeymap GdkHaikuKeymap;
#else
typedef GdkKeymap GdkHaikuKeymap;
#endif
typedef struct _GdkHaikuKeymapClass GdkHaikuKeymapClass;

GDK_AVAILABLE_IN_ALL
GType gdk_haiku_keymap_get_type (void);

G_END_DECLS

#endif /* __GDK_HAIKU_KEYS_H__ */
