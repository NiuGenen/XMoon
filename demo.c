#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

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

    XWindowChanges xwc;
    xwc.x = attrs.x;
    xwc.y = attrs.y;
    xwc.width  = attrs.width  / 2 + 1;
    xwc.height = attrs.height / 2 + 1;

    XConfigureWindow( dp, parent_win_ret,
          CWWidth | CWHeight, &xwc );

    XFree( child_win_list );
    XCloseDisplay( dp );

    return 0;
}
