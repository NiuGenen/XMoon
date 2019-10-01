#include "xm.h"
#include "xm-print.h"
#include "xm-event.h"

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

void win_div_2( Display *dp, Window win )
{
    XWindowChanges xwc;
    XWindowAttributes attrs;

    XGetWindowAttributes( dp, win, &attrs );

    if( attrs.class == InputOnly ){
        win = win_get_parent( dp, win, 0 );
        XGetWindowAttributes( dp, win, &attrs );
    }

    xwc.x = attrs.x;
    xwc.y = attrs.y;
    xwc.width  = GZERO(attrs.width  / 2);
    xwc.height = GZERO(attrs.height / 2);

    XConfigureWindow( dp, win,
          CWWidth | CWHeight, &xwc );
}

Bool simple_predicate(
       Display *dp,
       XEvent *event,
       XPointer arg  )
{
    if( event->type == KeyPress   ||
        event->type == KeyRelease ||
        event->type == FocusOut   ||
        event->type == FocusIn     )
        return 1;
    return 0;
}

int main()
{
    Display *dp;
    Screen  *sc;
    Window  win;

    // arg for XQueryTree
    Window root_win_ret, parent_win_ret;
    Window *child_win_list;
    unsigned int child_nr;

    // arg for XGetInputFocus
    Window curr_win;
    int      revert;

    XWindowAttributes attrs;

    unsigned int i = 0;

    Window saved_win;
    
    dp = xm_open_display_default_no_fail();
    print_display_info( dp );

    sc = xm_get_screen_of_display( dp, 0 );
    print_screen_info( sc );

    win = XRootWindowOfScreen( sc );

    XQueryTree( dp, win,
            &root_win_ret,   &parent_win_ret,
            &child_win_list, &child_nr );

    printf("Total Windows Number = %d\n", child_nr);
    printf("Parent Window = 0x%lx\n", UL(parent_win_ret) );
    printf("Root   Window = 0x%lx\n", UL(root_win_ret)   );
    for( i=0; i<MIN(child_nr,0); ++i ){
        Window _win = child_win_list[i];
        XGetWindowAttributes( dp, _win, &attrs );
        print_window_info( &attrs );
    }

    printf("\n--- test input focus ---\n");
    XGetInputFocus( dp, &curr_win, &revert);
    printf("input focus = 0x%lx\n", UL(curr_win));
    XGetWindowAttributes( dp, curr_win, &attrs );
    print_window_info( &attrs );

    XFree( child_win_list );

    XQueryTree( dp, curr_win,
            &root_win_ret, &parent_win_ret,
            &child_win_list, &child_nr);
    printf("Root   Window = 0x%lx\n", UL(root_win_ret)   );
    printf("Parent Window = 0x%lx\n", UL(parent_win_ret) );
    printf("Parent Window info :\n");
    XGetWindowAttributes( dp, parent_win_ret, &attrs );
    print_window_info( &attrs );

    saved_win = curr_win;
    while (1){
        XGetInputFocus( dp, &curr_win, &revert);
        printf("input focus = 0x%lx\n", UL(curr_win));
        if( saved_win != curr_win ){
            saved_win = curr_win;
            win_div_2( dp, curr_win );
        }
        sleep(1);
    }

    exit(0);

    // set event mask for key press/release event
    win_set_event_monitor( dp, curr_win, 
           KeyPressMask | KeyReleaseMask | FocusChangeMask );

    XEvent e;
    XKeyEvent *ee = NULL;
    while(1) {
        XIfEvent(dp, &e, simple_predicate, 0);
        printf("Event Type = %d\n", e.type);
        switch( e.type ){
        case KeyPress:
            ee = (XKeyEvent*)(&e);
            printf("Ket Press   = 0x%x\n", ee->keycode);
                break;
        case KeyRelease:
            ee = (XKeyEvent*)(&e);
            printf("Ket Release = 0x%x\n", ee->keycode);
                break;
        case FocusIn:
            win_clear_event_monitor( dp, curr_win );
            XGetInputFocus( dp, &curr_win, &revert);
            printf("Focus Move  to   0x%lx\n", curr_win);
            win_set_event_monitor( dp, curr_win, 
                    KeyPressMask | KeyReleaseMask | FocusChangeMask );
            break;
        case FocusOut:
            XGetInputFocus( dp, &curr_win, &revert);
            printf("Focus Leave from 0x%lx\n", curr_win);
            break;
        default:
            printf("Unsupport Event Type : %d\n", e.type);
            break;
        }
    }

    XFree( child_win_list );
    XCloseDisplay( dp );

    return 0;
}
