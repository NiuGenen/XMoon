#include "xm-print.h"

void print_display_info(
        Display *d )
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
