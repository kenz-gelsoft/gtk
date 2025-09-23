/* GDK - The GIMP Drawing Kit
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
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

/*
 * Private uninstalled header defining things local to the Wayland backend
 */

#ifndef __GDK_PRIVATE_WAYLAND_H__
#define __GDK_PRIVATE_WAYLAND_H__

#include <gdk/gdkcursor.h>
#include <gdk/gdkprivate.h>
#include <gdk/haiku/gdkhaiku.h>
#include <gdk/haiku/gdkdisplay-haiku.h>

#include <xkbcommon/xkbcommon.h>

#include "gdkinternals.h"
#include "haiku/gtk-primary-selection-client-protocol.h"

#include "config.h"

#define WL_SURFACE_HAS_BUFFER_SCALE 3
#define WL_POINTER_HAS_FRAME 5

#define GDK_WINDOW_IS_WAYLAND(win)    (GDK_IS_WINDOW_IMPL_WAYLAND (((GdkWindow *)win)->impl))

GdkKeymap *_gdk_haiku_keymap_new (void);
void       _gdk_haiku_keymap_update_from_fd (GdkKeymap *keymap,
                                               uint32_t   format,
                                               uint32_t   fd,
                                               uint32_t   size);
struct xkb_state *_gdk_haiku_keymap_get_xkb_state (GdkKeymap *keymap);
struct xkb_keymap *_gdk_haiku_keymap_get_xkb_keymap (GdkKeymap *keymap);
gboolean           _gdk_haiku_keymap_key_is_modifier (GdkKeymap *keymap,
                                                        guint      keycode);

void       _gdk_haiku_display_init_cursors (GdkHaikuDisplay *display);
void       _gdk_haiku_display_finalize_cursors (GdkHaikuDisplay *display);
void       _gdk_haiku_display_update_cursors (GdkHaikuDisplay *display);

struct wl_cursor_theme * _gdk_haiku_display_get_scaled_cursor_theme (GdkHaikuDisplay *display_haiku,
                                                                       guint              scale);

GdkCursor *_gdk_haiku_display_get_cursor_for_type (GdkDisplay    *display,
						     GdkCursorType  cursor_type);
GdkCursor *_gdk_haiku_display_get_cursor_for_type_with_scale (GdkDisplay    *display,
                                                                GdkCursorType  cursor_type,
                                                                guint          scale);
GdkCursor *_gdk_haiku_display_get_cursor_for_name (GdkDisplay  *display,
						     const gchar *name);
GdkCursor *_gdk_haiku_display_get_cursor_for_name_with_scale (GdkDisplay  *display,
                                                                const gchar *name,
                                                                guint        scale);
GdkCursor *_gdk_haiku_display_get_cursor_for_surface (GdkDisplay *display,
							cairo_surface_t *surface,
							gdouble     x,
							gdouble     y);
void       _gdk_haiku_display_get_default_cursor_size (GdkDisplay *display,
							 guint       *width,
							 guint       *height);
void       _gdk_haiku_display_get_maximal_cursor_size (GdkDisplay *display,
							 guint       *width,
							 guint       *height);
gboolean   _gdk_haiku_display_supports_cursor_alpha (GdkDisplay *display);
gboolean   _gdk_haiku_display_supports_cursor_color (GdkDisplay *display);

void       gdk_haiku_display_system_bell (GdkDisplay *display,
                                            GdkWindow  *window);

const char *_gdk_haiku_cursor_get_name (GdkCursor *cursor);

struct wl_buffer *_gdk_haiku_cursor_get_buffer (GdkCursor *cursor,
                                                  guint      image_index,
                                                  int       *hotspot_x,
                                                  int       *hotspot_y,
                                                  int       *w,
                                                  int       *h,
						  int       *scale);
guint      _gdk_haiku_cursor_get_next_image_index (GdkCursor *cursor,
                                                     guint      current_image_index,
                                                     guint     *next_image_delay);

void       _gdk_haiku_cursor_set_scale (GdkCursor *cursor,
                                          guint      scale);

GdkDragProtocol _gdk_haiku_window_get_drag_protocol (GdkWindow *window,
						       GdkWindow **target);

void            _gdk_haiku_window_register_dnd (GdkWindow *window);
GdkDragContext *_gdk_haiku_window_drag_begin (GdkWindow *window,
						GdkDevice *device,
						GList     *targets,
                                                gint       x_root,
                                                gint       y_root);
void            _gdk_haiku_window_offset_next_wl_buffer (GdkWindow *window,
                                                           int        x,
                                                           int        y);
GdkDragContext * _gdk_haiku_drop_context_new (GdkDisplay            *display,
                                                struct wl_data_device *data_device);
void _gdk_haiku_drag_context_set_source_window (GdkDragContext *context,
                                                  GdkWindow      *window);
void _gdk_haiku_drag_context_set_dest_window (GdkDragContext *context,
                                                GdkWindow      *dest_window,
                                                uint32_t        serial);
void _gdk_haiku_drag_context_emit_event (GdkDragContext *context,
                                           GdkEventType    type,
                                           guint32         time_);
void _gdk_haiku_drag_context_set_coords (GdkDragContext *context,
                                           gdouble         x,
                                           gdouble         y);

void gdk_haiku_drag_context_set_action (GdkDragContext *context,
                                          GdkDragAction   action);

GdkDragContext * gdk_haiku_drag_context_lookup_by_data_source   (struct wl_data_source *source);
GdkDragContext * gdk_haiku_drag_context_lookup_by_source_window (GdkWindow *window);
struct wl_data_source * gdk_haiku_drag_context_get_data_source  (GdkDragContext *context);

void gdk_haiku_drop_context_update_targets (GdkDragContext *context);

void _gdk_haiku_display_create_window_impl (GdkDisplay    *display,
					      GdkWindow     *window,
					      GdkWindow     *real_parent,
					      GdkScreen     *screen,
					      GdkEventMask   event_mask,
					      GdkWindowAttr *attributes,
					      gint           attributes_mask);

GdkWindow *_gdk_haiku_display_get_selection_owner (GdkDisplay *display,
						 GdkAtom     selection);
gboolean   _gdk_haiku_display_set_selection_owner (GdkDisplay *display,
						     GdkWindow  *owner,
						     GdkAtom     selection,
						     guint32     time,
						     gboolean    send_event);
void       _gdk_haiku_display_send_selection_notify (GdkDisplay *dispay,
						       GdkWindow        *requestor,
						       GdkAtom          selection,
						       GdkAtom          target,
						       GdkAtom          property,
						       guint32          time);
gint       _gdk_haiku_display_get_selection_property (GdkDisplay  *display,
							GdkWindow   *requestor,
							guchar     **data,
							GdkAtom     *ret_type,
							gint        *ret_format);
void       _gdk_haiku_display_convert_selection (GdkDisplay *display,
						   GdkWindow  *requestor,
						   GdkAtom     selection,
						   GdkAtom     target,
						   guint32     time);
gint        _gdk_haiku_display_text_property_to_utf8_list (GdkDisplay    *display,
							     GdkAtom        encoding,
							     gint           format,
							     const guchar  *text,
							     gint           length,
							     gchar       ***list);
gchar *     _gdk_haiku_display_utf8_to_string_target (GdkDisplay  *display,
							const gchar *str);

GdkDeviceManager *_gdk_haiku_device_manager_new (GdkDisplay *display);
void              _gdk_haiku_device_manager_add_seat (GdkDeviceManager *device_manager,
                                                        guint32           id,
						        struct wl_seat   *seat);
void              _gdk_haiku_device_manager_remove_seat (GdkDeviceManager *device_manager,
                                                           guint32           id);

GdkKeymap *_gdk_haiku_device_get_keymap (GdkDevice *device);
uint32_t _gdk_haiku_device_get_implicit_grab_serial(GdkHaikuDevice *device,
                                                      const GdkEvent   *event);
uint32_t _gdk_haiku_seat_get_last_implicit_grab_serial (GdkSeat           *seat,
                                                          GdkEventSequence **seqence);
GdkWindow * gdk_haiku_device_get_focus (GdkDevice *device);
struct wl_data_device * gdk_haiku_device_get_data_device (GdkDevice *gdk_device);
void gdk_haiku_seat_set_selection (GdkSeat               *seat,
                                     struct wl_data_source *source);

void gdk_haiku_seat_set_primary (GdkSeat  *seat,
                                   gpointer  source);

GdkDragContext * gdk_haiku_device_get_drop_context (GdkDevice *gdk_device);

void gdk_haiku_device_unset_touch_grab (GdkDevice        *device,
                                          GdkEventSequence *sequence);

void     _gdk_haiku_display_deliver_event (GdkDisplay *display, GdkEvent *event);
GSource *_gdk_haiku_display_event_source_new (GdkDisplay *display);
void     _gdk_haiku_display_queue_events (GdkDisplay *display);

GdkAppLaunchContext *_gdk_haiku_display_get_app_launch_context (GdkDisplay *display);

GdkDisplay *_gdk_haiku_display_open (const gchar *display_name);

GdkWindow *_gdk_haiku_screen_create_root_window (GdkScreen *screen,
						   int width,
						   int height);

GdkScreen *_gdk_haiku_screen_new (GdkDisplay *display);
void _gdk_haiku_screen_add_output (GdkScreen        *screen,
                                     guint32           id,
                                     struct wl_output *output,
				     guint32           version);
void _gdk_haiku_screen_remove_output (GdkScreen *screen,
                                        guint32 id);
int _gdk_haiku_screen_get_output_refresh_rate (GdkScreen        *screen,
                                                 struct wl_output *output);
guint32 _gdk_haiku_screen_get_output_scale (GdkScreen        *screen,
					      struct wl_output *output);
struct wl_output *_gdk_haiku_screen_get_wl_output (GdkScreen *screen,
                                                     gint monitor_num);

void _gdk_haiku_screen_set_has_gtk_shell (GdkScreen       *screen);

void _gdk_haiku_screen_init_xdg_output (GdkScreen *screen);

void _gdk_haiku_window_set_grab_seat (GdkWindow      *window,
                                        GdkSeat        *seat);

guint32 _gdk_haiku_display_get_serial (GdkHaikuDisplay *display_haiku);
void _gdk_haiku_display_update_serial (GdkHaikuDisplay *display_haiku,
                                         guint32            serial);

cairo_surface_t * _gdk_haiku_display_create_shm_surface (GdkHaikuDisplay *display,
                                                           int                width,
                                                           int                height,
                                                           guint              scale);
struct wl_buffer *_gdk_haiku_shm_surface_get_wl_buffer (cairo_surface_t *surface);
gboolean _gdk_haiku_is_shm_surface (cairo_surface_t *surface);

GdkHaikuSelection * gdk_haiku_display_get_selection (GdkDisplay *display);
GdkHaikuSelection * gdk_haiku_selection_new (void);
void gdk_haiku_selection_free (GdkHaikuSelection *selection);

void gdk_haiku_selection_ensure_offer (GdkDisplay           *display,
                                         struct wl_data_offer *wl_offer);
void gdk_haiku_selection_ensure_primary_offer (GdkDisplay *display,
                                                 gpointer    wp_offer);

void gdk_haiku_selection_set_offer (GdkDisplay           *display,
                                      GdkAtom               selection,
                                      gpointer              offer);
gpointer gdk_haiku_selection_get_offer (GdkDisplay *display,
                                          GdkAtom     selection);
GList * gdk_haiku_selection_get_targets (GdkDisplay *display,
                                           GdkAtom     selection);

void     gdk_haiku_selection_store   (GdkWindow    *window,
                                        GdkAtom       type,
                                        GdkPropMode   mode,
                                        const guchar *data,
                                        gint          len);
struct wl_data_source * gdk_haiku_selection_get_data_source (GdkWindow *owner,
                                                               GdkAtom    selection);
void gdk_haiku_selection_unset_data_source (GdkDisplay *display, GdkAtom selection);
gboolean gdk_haiku_selection_set_current_offer_actions (GdkDisplay *display,
                                                          uint32_t    actions);

EGLSurface gdk_haiku_window_get_egl_surface (GdkWindow *window,
                                               EGLConfig config);
EGLSurface gdk_haiku_window_get_dummy_egl_surface (GdkWindow *window,
						     EGLConfig config);

struct gtk_surface1 * gdk_haiku_window_get_gtk_surface (GdkWindow *window);

void gdk_haiku_seat_set_global_cursor (GdkSeat   *seat,
                                         GdkCursor *cursor);

struct wl_output *gdk_haiku_window_get_wl_output (GdkWindow *window);

void gdk_haiku_window_inhibit_shortcuts (GdkWindow *window,
                                           GdkSeat   *gdk_seat);
void gdk_haiku_window_restore_shortcuts (GdkWindow *window,
                                           GdkSeat   *gdk_seat);

#endif /* __GDK_PRIVATE_WAYLAND_H__ */
