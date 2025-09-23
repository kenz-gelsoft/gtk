/*
 * Copyright © 2016 Red Hat, Inc
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "config.h"

#include <glib.h>
#include <gio/gio.h>
#include "gdkprivate-haiku.h"

#include "gdkmonitor-haiku.h"

G_DEFINE_TYPE (GdkHaikuMonitor, gdk_haiku_monitor, GDK_TYPE_MONITOR)

static void
gdk_haiku_monitor_init (GdkHaikuMonitor *monitor)
{
}

static void
gdk_haiku_monitor_finalize (GObject *object)
{
  GdkHaikuMonitor *monitor = (GdkHaikuMonitor *)object;

  g_free (monitor->name);

  wl_output_destroy (monitor->output);

  G_OBJECT_CLASS (gdk_haiku_monitor_parent_class)->finalize (object);
}

static void
gdk_haiku_monitor_class_init (GdkHaikuMonitorClass *class)
{
  G_OBJECT_CLASS (class)->finalize = gdk_haiku_monitor_finalize;
}

/**
 * gdk_haiku_monitor_get_wl_output:
 * @monitor: (type GdkHaikuMonitor): a #GdkMonitor
 *
 * Returns the Wayland wl_output of a #GdkMonitor.
 *
 * Returns: (transfer none): a Wayland wl_output
 * Since: 3.22
 */
struct wl_output *
gdk_haiku_monitor_get_wl_output (GdkMonitor *monitor)
{
  g_return_val_if_fail (GDK_IS_HAIKU_MONITOR (monitor), NULL);

  return GDK_HAIKU_MONITOR (monitor)->output;
}
