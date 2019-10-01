#include "xm.h"

inline Display *xm_open_display_default()
{
    return XOpenDisplay(":0");
}

inline Display *xm_open_display_default_no_fail()
{
    Display *d = xm_open_display_default();
    if( d == NULL ){
        fprintf(stderr, "[xm] fail to open display\n");
        exit(-1);
    }
    return d;
}

inline Screen *xm_get_screen_of_display( Display *d, int idx )
{
    return XScreenOfDisplay( d, idx );
}

Window win_get_parent(
    Display *dp,
    Window  win,
    int     allow_inputonly )
{
    printf("Search Parent for window 0x%lx\n", win);

    Window          root_win_ret;
    Window          parent_win_ret;
    Window          *child_win_list;
    unsigned int    child_nr;

    XWindowAttributes attrs;

    do{
        XQueryTree( dp, win,
            &root_win_ret, &parent_win_ret,
            &child_win_list, &child_nr);

        printf("Parent Window = 0x%lx\n", UL(parent_win_ret) );

        if( allow_inputonly )
            goto _OUT_;

        XGetWindowAttributes( dp, parent_win_ret, &attrs );
    }while( attrs.class == InputOnly );

_OUT_:
    XFree( child_win_list );
    return parent_win_ret;
}
