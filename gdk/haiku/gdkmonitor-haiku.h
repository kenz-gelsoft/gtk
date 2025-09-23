/*
 * Copyright © 2017 Tom Schoonjans
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

#ifndef __GDK_HAIKU_MONITOR_PRIVATE_H__
#define __GDK_HAIKU_MONITOR_PRIVATE_H__

#include <glib.h>
#include <gio/gio.h>
//#include <AppKit/AppKit.h>

#include "gdkmonitorprivate.h"

#include "gdkhaikumonitor.h"
#include "gdkprivate-haiku.h"

struct _GdkHaikuMonitor
{
  GdkMonitor parent;
//  CGDirectDisplayID id;
};

struct _GdkHaikuMonitorClass {
  GdkMonitorClass parent_class;
};

#endif
