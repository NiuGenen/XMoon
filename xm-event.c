#include "xm-event.h"

void win_set_event_monitor(
        Display *dp,
        Window  win,
        unsigned long mask )
{
    XSetWindowAttributes xwa;

    EVENT_CLEAR_MASK(xwa.event_mask);

    EVENT_ADD_MASK(xwa.event_mask, mask);

    XChangeWindowAttributes( dp, win, 
          CWEventMask, &xwa);
}

void win_clear_event_monitor(
        Display *dp,
        Window  win )
{
    XSetWindowAttributes xwa;

    EVENT_CLEAR_MASK(xwa.event_mask);

    XChangeWindowAttributes( dp, win, 
          CWEventMask, &xwa);
}
