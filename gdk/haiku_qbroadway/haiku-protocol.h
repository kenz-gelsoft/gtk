#ifndef __HAIKU_PROTOCOL_H__
#define __HAIKU_PROTOCOL_H__

#include <glib.h>

typedef struct  {
    gint32 x, y;
    gint32 width, height;
} HaikuRect;

typedef enum {
  HAIKU_EVENT_ENTER = 'e',
  HAIKU_EVENT_LEAVE = 'l',
  HAIKU_EVENT_POINTER_MOVE = 'm',
  HAIKU_EVENT_BUTTON_PRESS = 'b',
  HAIKU_EVENT_BUTTON_RELEASE = 'B',
  HAIKU_EVENT_TOUCH = 't',
  HAIKU_EVENT_SCROLL = 's',
  HAIKU_EVENT_KEY_PRESS = 'k',
  HAIKU_EVENT_KEY_RELEASE = 'K',
  HAIKU_EVENT_GRAB_NOTIFY = 'g',
  HAIKU_EVENT_UNGRAB_NOTIFY = 'u',
  HAIKU_EVENT_CONFIGURE_NOTIFY = 'w',
  HAIKU_EVENT_DELETE_NOTIFY = 'W',
  HAIKU_EVENT_SCREEN_SIZE_CHANGED = 'd',
  HAIKU_EVENT_FOCUS = 'f'
} HaikuEventType;

typedef enum {
  HAIKU_OP_GRAB_POINTER = 'g',
  HAIKU_OP_UNGRAB_POINTER = 'u',
  HAIKU_OP_NEW_SURFACE = 's',
  HAIKU_OP_SHOW_SURFACE = 'S',
  HAIKU_OP_HIDE_SURFACE = 'H',
  HAIKU_OP_RAISE_SURFACE = 'r',
  HAIKU_OP_LOWER_SURFACE = 'R',
  HAIKU_OP_DESTROY_SURFACE = 'd',
  HAIKU_OP_MOVE_RESIZE = 'm',
  HAIKU_OP_SET_TRANSIENT_FOR = 'p',
  HAIKU_OP_PUT_RGB = 'i',
  HAIKU_OP_REQUEST_AUTH = 'l',
  HAIKU_OP_AUTH_OK = 'L',
  HAIKU_OP_DISCONNECTED = 'D',
  HAIKU_OP_PUT_BUFFER = 'b',
  HAIKU_OP_SET_SHOW_KEYBOARD = 'k',
} HaikuOpType;

typedef struct {
  guint32 type;
  guint32 serial;
  guint64 time;
} HaikuInputBaseMsg;

typedef struct {
  HaikuInputBaseMsg base;
  guint32 mouse_window_id; /* The real window, not taking grabs into account */
  guint32 event_window_id;
  gint32 root_x;
  gint32 root_y;
  gint32 win_x;
  gint32 win_y;
  guint32 state;
} HaikuInputPointerMsg;

typedef struct {
  HaikuInputPointerMsg pointer;
  guint32 mode;
} HaikuInputCrossingMsg;

typedef struct {
  HaikuInputPointerMsg pointer;
  guint32 button;
} HaikuInputButtonMsg;

typedef struct {
  HaikuInputPointerMsg pointer;
  gint32 dir;
} HaikuInputScrollMsg;

typedef struct {
  HaikuInputBaseMsg base;
  guint32 touch_type;
  guint32 event_window_id;
  guint32 sequence_id;
  guint32 is_emulated;
  gint32 root_x;
  gint32 root_y;
  gint32 win_x;
  gint32 win_y;
  guint32 state;
} HaikuInputTouchMsg;

typedef struct {
  HaikuInputBaseMsg base;
  guint32 window_id;
  guint32 state;
  gint32 key;
} HaikuInputKeyMsg;

typedef struct {
  HaikuInputBaseMsg base;
  gint32 res;
} HaikuInputGrabReply;

typedef struct {
  HaikuInputBaseMsg base;
  gint32 id;
  gint32 x;
  gint32 y;
  gint32 width;
  gint32 height;
} HaikuInputConfigureNotify;

typedef struct {
  HaikuInputBaseMsg base;
  guint32 width;
  guint32 height;
} HaikuInputScreenResizeNotify;

typedef struct {
  HaikuInputBaseMsg base;
  gint32 id;
} HaikuInputDeleteNotify;

typedef struct {
  HaikuInputBaseMsg base;
  gint32 new_id;
  gint32 old_id;
} HaikuInputFocusMsg;

typedef union {
  HaikuInputBaseMsg base;
  HaikuInputPointerMsg pointer;
  HaikuInputCrossingMsg crossing;
  HaikuInputButtonMsg button;
  HaikuInputScrollMsg scroll;
  HaikuInputTouchMsg touch;
  HaikuInputKeyMsg key;
  HaikuInputGrabReply grab_reply;
  HaikuInputConfigureNotify configure_notify;
  HaikuInputDeleteNotify delete_notify;
  HaikuInputScreenResizeNotify screen_resize_notify;
  HaikuInputFocusMsg focus;
} HaikuInputMsg;

typedef enum {
  HAIKU_REQUEST_NEW_WINDOW,
  HAIKU_REQUEST_FLUSH,
  HAIKU_REQUEST_SYNC,
  HAIKU_REQUEST_QUERY_MOUSE,
  HAIKU_REQUEST_DESTROY_WINDOW,
  HAIKU_REQUEST_SHOW_WINDOW,
  HAIKU_REQUEST_HIDE_WINDOW,
  HAIKU_REQUEST_SET_TRANSIENT_FOR,
  HAIKU_REQUEST_UPDATE,
  HAIKU_REQUEST_MOVE_RESIZE,
  HAIKU_REQUEST_GRAB_POINTER,
  HAIKU_REQUEST_UNGRAB_POINTER,
  HAIKU_REQUEST_FOCUS_WINDOW,
  HAIKU_REQUEST_SET_SHOW_KEYBOARD,
  HAIKU_REQUEST_SET_MODAL_HINT
} HaikuRequestType;

typedef struct {
  guint32 size;
  guint32 serial;
  guint32 type;
} HaikuRequestBase, HaikuRequestFlush, HaikuRequestSync, HaikuRequestQueryMouse;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
} HaikuRequestDestroyWindow, HaikuRequestShowWindow, HaikuRequestHideWindow, HaikuRequestFocusWindow;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  guint32 parent;
} HaikuRequestSetTransientFor;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  gint32 dx;
  gint32 dy;
  guint32 n_rects;
  HaikuRect rects[1];
} HaikuRequestTranslate;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  char name[36];
  guint32 width;
  guint32 height;
} HaikuRequestUpdate;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  guint32 owner_events;
  guint32 event_mask;
  guint32 time_;
} HaikuRequestGrabPointer;

typedef struct {
  HaikuRequestBase base;
  guint32 time_;
} HaikuRequestUngrabPointer;

typedef struct {
  HaikuRequestBase base;
  gint32 x;
  gint32 y;
  guint32 width;
  guint32 height;
  guint32 is_temp;
} HaikuRequestNewWindow;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  guint32 with_move;
  gint32 x;
  gint32 y;
  guint32 width;
  guint32 height;
} HaikuRequestMoveResize;

typedef struct {
  HaikuRequestBase base;
  guint32 show_keyboard;
} HaikuRequestSetShowKeyboard;

typedef struct {
  HaikuRequestBase base;
  guint32 id;
  gboolean modal_hint;
} HaikuRequestSetModalHint;

typedef union {
  HaikuRequestBase base;
  HaikuRequestNewWindow new_window;
  HaikuRequestFlush flush;
  HaikuRequestSync sync;
  HaikuRequestQueryMouse query_mouse;
  HaikuRequestDestroyWindow destroy_window;
  HaikuRequestShowWindow show_window;
  HaikuRequestHideWindow hide_window;
  HaikuRequestSetTransientFor set_transient_for;
  HaikuRequestUpdate update;
  HaikuRequestMoveResize move_resize;
  HaikuRequestGrabPointer grab_pointer;
  HaikuRequestUngrabPointer ungrab_pointer;
  HaikuRequestTranslate translate;
  HaikuRequestFocusWindow focus_window;
  HaikuRequestSetShowKeyboard set_show_keyboard;
  HaikuRequestSetModalHint set_modal_hint;
} HaikuRequest;

typedef enum {
  HAIKU_REPLY_EVENT,
  HAIKU_REPLY_SYNC,
  HAIKU_REPLY_QUERY_MOUSE,
  HAIKU_REPLY_NEW_WINDOW,
  HAIKU_REPLY_GRAB_POINTER,
  HAIKU_REPLY_UNGRAB_POINTER
} HaikuReplyType;

typedef struct {
  guint32 size;
  guint32 in_reply_to;
  guint32 type;
} HaikuReplyBase, HaikuReplySync;

typedef struct {
  HaikuReplyBase base;
  guint32 id;
} HaikuReplyNewWindow;

typedef struct {
  HaikuReplyBase base;
  guint32 status;
} HaikuReplyGrabPointer, HaikuReplyUngrabPointer;

typedef struct {
  HaikuReplyBase base;
  guint32 toplevel;
  gint32 root_x;
  gint32 root_y;
  guint32 mask;
} HaikuReplyQueryMouse;

typedef struct {
  HaikuReplyBase base;
  HaikuInputMsg msg;
} HaikuReplyEvent;

typedef union {
  HaikuReplyBase base;
  HaikuReplyEvent event;
  HaikuReplyQueryMouse query_mouse;
  HaikuReplyNewWindow new_window;
  HaikuReplyGrabPointer grab_pointer;
  HaikuReplyUngrabPointer ungrab_pointer;
} HaikuReply;

#endif /* __HAIKU_PROTOCOL_H__ */
