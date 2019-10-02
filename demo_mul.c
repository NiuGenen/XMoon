#include "xm.h"

void win_mul_2( Display *dp, Window win )
{
    XWindowChanges xwc;
    XWindowAttributes attrs;

    XGetWindowAttributes( dp, win, &attrs );

    xwc.x = attrs.x;
    xwc.y = attrs.y;
    xwc.width  = attrs.width  * 2;
    xwc.height = attrs.height * 2;
    xwc.width  = GZERO(xwc.width );
    xwc.height = GZERO(xwc.height);

    XConfigureWindow( dp, win,
          CWWidth | CWHeight, &xwc );
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

    win_mul_2( dp, win );

    XCloseDisplay( dp );

    return 0;
}
