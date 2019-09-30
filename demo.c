#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#define GZERO(x) ((x)==0?1:(x))

#define EVENT_ADD_MASK(e,m) (e=(e)|(m))
#define EVENT_CLEAR_MASK(e) (e=0)

#define UL(x) ((unsigned long)(x))

inline Display *xm_open_display()
{
    return XOpenDisplay(":0");
}

inline Display *xm_open_display_no_fail()
{
    Display *d = xm_open_display();
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

void print_display_info( Display *d )
{
    printf("------ display info ------\n");

    /*Display *_d = d;*/

    /*printf("------ screen info ------\n");*/
    
    /*printf("vendor      = %s\n" , _d->vendor       );*/
    /*printf("qlen        = %d\n" , _d->qlen         );*/
    /*printf("name        = %s\n" , _d->display_name );*/
    /*printf("nscreens    = %d\n" , _d->nscreens     );*/
    /*printf("request     = %ld\n", _d->request      );*/
    /*printf("last_req_rd = %ld\n", _d->request      );*/
    /*printf("min_key     = %d\n" , _d->min_keycode  );*/
    /*printf("max_key     = %d\n" , _d->max_keycode  );*/

    printf("--------------------------\n");
}

void print_screen_info( Screen *sc )
{
    int i = 0;

    printf("------ screen info ------\n");

    printf("width     = %d\n", sc->width   );
    printf("height    = %d\n", sc->height  );
    printf("mwidth    = %d\n", sc->mwidth  );
    printf("mheight   = %d\n", sc->mheight );
    printf("ndepths   = %d\n", sc->ndepths );

    for( i=0; i<sc->ndepths; ++i )
        printf("depth[%2d] = %2d, nvisuals = %2d\n",
                i, sc->depths[i].depth, sc->depths[i].nvisuals);

    printf("w_pixel   = %ld\n", sc->white_pixel );
    printf("b_pixel   = %ld\n", sc->black_pixel );
    printf("max_maps  = %d\n" , sc->max_maps    );
    printf("min_maps  = %d\n" , sc->min_maps    );

    printf("-------------------------\n");
}

void print_window_info( XWindowAttributes *a )
{
    printf("------ window ------\n");

    printf("x      = %d\n"   ,  a->x        );
    printf("y      = %d\n"   ,  a->y        );
    printf("width  = %d\n"   ,  a->width    );
    printf("height = %d\n"   ,  a->height   );
    printf("depth  = %d\n"   ,  a->depth    );
    printf("root   = 0x%lx\n",  UL(a->root) );
    printf("class  = %d\n"   ,  a->class    );

    printf("--------------------\n");
}

void win_mul_2( Display *dp, Window win )
{
    XWindowChanges xwc;
    XWindowAttributes attrs;

    XGetWindowAttributes( dp, win, &attrs );

    xwc.x = attrs.x;
    xwc.y = attrs.y;
    xwc.width  = attrs.width  / 2;
    xwc.height = attrs.height / 2;
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

    xwc.x = attrs.x;
    xwc.y = attrs.y;
    xwc.width  = GZERO(attrs.width ) * 2;
    xwc.height = GZERO(attrs.height) * 2;

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
    
    dp = xm_open_display_no_fail();
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

    while (1){
        XGetInputFocus( dp, &curr_win, &revert);
        printf("input focus = 0x%lx\n", UL(curr_win));
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
