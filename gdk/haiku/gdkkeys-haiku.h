/* gdkkeys-haiku.h
 *
 * Copyright (C) 2005-2007 Imendio AB
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

#ifndef __GDK_KEYS_QUARTZ_H__
#define __GDK_KEYS_QUARTZ_H__
#if MAC_OS_X_VERSION_MIN_REQUIRED < 101200
typedef enum
  {
    GDK_HAIKU_FLAGS_CHANGED = NSFlagsChanged,
    GDK_HAIKU_KEY_UP = NSKeyUp,
    GDK_HAIKU_KEY_DOWN = NSKeyDown,
    GDK_HAIKU_MOUSE_ENTERED = NSMouseEntered,
    GDK_HAIKU_MOUSE_EXITED = NSMouseExited,
    GDK_HAIKU_SCROLL_WHEEL = NSScrollWheel,
    GDK_HAIKU_MOUSE_MOVED = NSMouseMoved,
    GDK_HAIKU_OTHER_MOUSE_DRAGGED = NSOtherMouseDragged,
    GDK_HAIKU_RIGHT_MOUSE_DRAGGED = NSRightMouseDragged,
    GDK_HAIKU_LEFT_MOUSE_DRAGGED = NSLeftMouseDragged,
    GDK_HAIKU_OTHER_MOUSE_UP = NSOtherMouseUp,
    GDK_HAIKU_RIGHT_MOUSE_UP = NSRightMouseUp,
    GDK_HAIKU_LEFT_MOUSE_UP = NSLeftMouseUp,
    GDK_HAIKU_OTHER_MOUSE_DOWN = NSOtherMouseDown,
    GDK_HAIKU_RIGHT_MOUSE_DOWN = NSRightMouseDown,
    GDK_HAIKU_LEFT_MOUSE_DOWN = NSLeftMouseDown,
  } GdkHaikuEventType;

typedef enum
  {
    GDK_HAIKU_ALTERNATE_KEY_MASK = NSAlternateKeyMask,
    GDK_HAIKU_CONTROL_KEY_MASK = NSControlKeyMask,
    GDK_HAIKU_SHIFT_KEY_MASK = NSShiftKeyMask,
    GDK_HAIKU_ALPHA_SHIFT_KEY_MASK = NSAlphaShiftKeyMask,
    GDK_HAIKU_COMMAND_KEY_MASK = NSCommandKeyMask,
    GDK_HAIKU_ANY_EVENT_MASK = NSAnyEventMask,
  } GdkHaikuEventModifierFlags;


#else
typedef enum
  {
    GDK_HAIKU_FLAGS_CHANGED = NSEventTypeFlagsChanged,
    GDK_HAIKU_KEY_UP = NSEventTypeKeyUp,
    GDK_HAIKU_KEY_DOWN = NSEventTypeKeyDown,
    GDK_HAIKU_MOUSE_ENTERED = NSEventTypeMouseEntered,
    GDK_HAIKU_MOUSE_EXITED = NSEventTypeMouseExited,
    GDK_HAIKU_SCROLL_WHEEL = NSEventTypeScrollWheel,
    GDK_HAIKU_MOUSE_MOVED = NSEventTypeMouseMoved,
    GDK_HAIKU_OTHER_MOUSE_DRAGGED = NSEventTypeOtherMouseDragged,
    GDK_HAIKU_RIGHT_MOUSE_DRAGGED = NSEventTypeRightMouseDragged,
    GDK_HAIKU_LEFT_MOUSE_DRAGGED = NSEventTypeLeftMouseDragged,
    GDK_HAIKU_OTHER_MOUSE_UP = NSEventTypeOtherMouseUp,
    GDK_HAIKU_RIGHT_MOUSE_UP = NSEventTypeRightMouseUp,
    GDK_HAIKU_LEFT_MOUSE_UP = NSEventTypeLeftMouseUp,
    GDK_HAIKU_OTHER_MOUSE_DOWN = NSEventTypeOtherMouseDown,
    GDK_HAIKU_RIGHT_MOUSE_DOWN = NSEventTypeRightMouseDown,
    GDK_HAIKU_LEFT_MOUSE_DOWN = NSEventTypeLeftMouseDown,
  } GdkHaikuEventType;

typedef enum
  {
   GDK_HAIKU_ALTERNATE_KEY_MASK = NSEventModifierFlagOption,
   GDK_HAIKU_CONTROL_KEY_MASK = NSEventModifierFlagControl,
   GDK_HAIKU_SHIFT_KEY_MASK = NSEventModifierFlagShift,
   GDK_HAIKU_ALPHA_SHIFT_KEY_MASK = NSEventModifierFlagCapsLock,
   GDK_HAIKU_COMMAND_KEY_MASK = NSEventModifierFlagCommand,
  } GdkHaikuEventModifierFlags;


#endif
#endif /* __GDK_KEYS_QUARTZ_H__ */
