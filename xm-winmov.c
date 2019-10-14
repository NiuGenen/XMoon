#include "xm.h"

enum win_pos_type{
    wp_center     ,
    wp_left       ,
    wp_right      ,
    wp_up_left    ,
    wp_down_left  ,
    wp_up_right   ,
    wp_down_right
};

typedef struct win_pos_t {
    int type;
    int x;
    int y;
    int w;
    int h;
}win_pos_t;

win_pos_t win_pos_all[] = {
    {wp_center,  290,  250, 1240,  650},
    {wp_left,      0,   54,  960, 1026},
    {wp_right,   960,   54,  960, 1026}
};

#define WIN_MOV_FUNC(name) \
void win_mov_##name ( Display *dp, Window win ) {\
    XWindowChanges xwc; \
    XWindowAttributes attrs; \
    XGetWindowAttributes( dp, win, &attrs ); \
    if( attrs.class == InputOnly ){ \
        win = win_get_parent( dp, win, 0 ); \
        XGetWindowAttributes( dp, win, &attrs ); \
    } \
    xwc.x      = win_pos_all[ wp_##name ].x; \
    xwc.y      = win_pos_all[ wp_##name ].y; \
    xwc.width  = win_pos_all[ wp_##name ].w; \
    xwc.height = win_pos_all[ wp_##name ].h; \
    XConfigureWindow( dp, win, CWX | CWY | CWWidth | CWHeight, &xwc ); \
}

WIN_MOV_FUNC(center);
WIN_MOV_FUNC(left);
WIN_MOV_FUNC(right);

int main (int argc, char *arhv[])
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

    /*win_mov_center( dp, win );*/
    win_mov_left( dp, win );

    XCloseDisplay( dp );

    return 0;
}
