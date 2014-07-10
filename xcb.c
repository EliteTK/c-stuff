#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
        int i, screen_num;
        xcb_connection_t *connection = xcb_connect(NULL, &screen_num);

        const xcb_setup_t *setup = xcb_get_setup(connection);
        xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);

        for (i = 0; i < screen_num; i++) {
                xcb_screen_next(&iter);
        }

        xcb_screen_t *screen = iter.data;

        printf("\n");
        printf("Information about screen %"PRIu32":\n", screen->root);
        printf("  width         : %"PRIu16"\n", screen->width_in_pixels);
        printf("  height        : %"PRIu16"\n", screen->height_in_pixels);
        printf("  white pixel   : %"PRIu32"\n", screen->white_pixel);
        printf("  black pixel   : %"PRIu32"\n", screen->black_pixel);

        xcb_disconnect(connection);
        return 0;
}
