#ifndef _XM_H_
#define _XM_H_

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#define GZERO(x) ((x)==0?1:(x))
#define UL(x) ((unsigned long)(x))

inline Display *xm_open_display_default();
inline Display *xm_open_display_default_no_fail();

inline Screen  *xm_get_screen_of_display( Display *d, int idx );

Window win_get_parent(
    Display *dp,
    Window  win,
    int     allow_inputonly );

/*
 * XWindowAttributes
 * copt from X11/Xlib.h
 *
typedef struct {
    int             x, y;			        // location of window 
    int             width, height;		    // width and height of window 
    int             border_width;		    // border width of window 
    int             depth;          	    // depth of window 
    Visual          *visual;		        // the associated visual structure
    Window          root;        	        // root of screen containing window 
#if defined(__cplusplus) || defined(c_plusplus)
    int             c_class;		        // C++ InputOutput, InputOnly
#else
    int             class;			        // InputOutput, InputOnly
#endif
    int             bit_gravity;		    // one of bit gravity values 
    int             win_gravity;		    // one of the window gravity values 
    int             backing_store;		    // NotUseful, WhenMapped, Always 
    unsigned long   backing_planes;         // planes to be preserved if possible
    unsigned long   backing_pixel;          // value to be used when restoring planes 
    Bool            save_under;		        // boolean, should bits under be saved? 
    Colormap        colormap;		        // color map to be associated with window 
    Bool            map_installed;		    // boolean, is color map currently installed
    int             map_state;		        // IsUnmapped, IsUnviewable, IsViewable
    long            all_event_masks;	    // set of events all people have interest in
    long            your_event_mask;	    // my event mask
    long            do_not_propagate_mask;  // set of events that should not propagate
    Bool            override_redirect;	    // boolean value for override-redirect
    Screen          *screen;		        // back pointer to correct screen
} XWindowAttributes;
 */


#endif // _XM_H_
