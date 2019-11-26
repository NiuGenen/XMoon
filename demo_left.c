#include "xm.h"

void win_left( Display *dp, Window win )
{
    XWindowChanges xwc;
    XWindowAttributes attrs;

    XGetWindowAttributes( dp, win, &attrs );

    if( attrs.class == InputOnly ){
        win = win_get_parent( dp, win, 0 );
        XGetWindowAttributes( dp, win, &attrs );
    }

    xwc.x = 125;
    xwc.y = 109;
    xwc.width  = 809;
    xwc.height = 892;

    XConfigureWindow( dp, win,
          CWX | CWY | CWWidth | CWHeight, &xwc );
}

int main()
{
    Display *dp;
    Screen  *sc;
    Window  win;

    // arg for XGetInputFocus
    Window curr_win;
    int      revert;
    
    XWindowAttributes attrs;

    dp = xm_open_display_default_no_fail();

    XGetInputFocus( dp, &curr_win, &revert);

    XGetWindowAttributes( dp, curr_win, &attrs );
    if( attrs.class == InputOnly ){
        win = win_get_parent( dp, curr_win, 0 );
    } else{
        win = curr_win;
    }

    win_left( dp, win );

    XCloseDisplay( dp );

    return 0;
}
