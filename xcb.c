/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */

#include <stdlib.h>
#include <stdio.h>
#include <xcb/xcb.h>

int main(int argc, char **argv)
{
        xcb_point_t points[] = {
                {10, 10},
                {10, 20},
                {20, 10},
                {20, 20}
        };

        xcb_point_t polyline[] = {
                {50, 10},
                { 5, 20},
                {20,-20},
                {10, 10}
        };

        xcb_segment_t segments[] = {
                {100, 10, 140, 30},
                {110, 25, 130, 60}
        };

        xcb_rectangle_t rectangles[] = {
                {10, 50, 40, 20},
                {80, 50, 10, 40}
        };

        xcb_arc_t arcs[] = {
                {10, 100, 60, 40, 0, 90 << 6},
                {90, 100, 55, 40, 0, 270 << 6}
        };

        xcb_connection_t *connection = xcb_connect(NULL, NULL);

        xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

        xcb_drawable_t window = screen->root;
        xcb_gcontext_t foreground = xcb_generate_id(connection);
        uint32_t       mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
        uint32_t       values[2] = { screen->black_pixel, 0};

        xcb_create_gc(connection, foreground, window, mask, values);

        window = xcb_generate_id(connection);

        mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
        values[0] = screen->white_pixel;
        values[1] = XCB_EVENT_MASK_EXPOSURE;

        xcb_create_window(connection,
                        screen->root_depth,
                        window,
                        screen->root,
                        0, 0,
                        150, 150,
                        10,
                        XCB_WINDOW_CLASS_INPUT_OUTPUT,
                        screen->root_visual,
                        mask, values);

        xcb_map_window(connection, window);
        xcb_flush(connection);

        printf("Window mapped.\n");

        xcb_generic_event_t *event;
        while ((event = xcb_wait_for_event(connection))) {
                printf("We're waiting.\n");
                switch (event->response_type & ~0x80) {
                case XCB_EXPOSE:
                        printf("Expose event.\n");
                        xcb_poly_point(connection,
                                        XCB_COORD_MODE_ORIGIN,
                                        window,
                                        foreground,
                                        4, points);
                        xcb_poly_line(connection,
                                        XCB_COORD_MODE_PREVIOUS,
                                        window,
                                        foreground,
                                        4, polyline);
                        xcb_poly_segment(connection,
                                        window,
                                        foreground,
                                        2, segments);
                        xcb_poly_rectangle(connection,
                                        window,
                                        foreground,
                                        2, rectangles);
                        xcb_poly_arc(connection,
                                        window,
                                        foreground,
                                        2, arcs);
                        xcb_flush(connection);

                        break;
                default:
                        break;
                }

                free(event);
        }

        printf("We did derp.\n");

        xcb_disconnect(connection);

/*#include <stdbool.h>*/
/*#include <stdio.h>*/
/*#include <stdlib.h>*/
/*#include <xcb/xcb.h>*/
/*#include <inttypes.h>*/

/*int main(int argc, char **argv)*/
/*{*/
        /*int i, screen_num;*/
        /*xcb_connection_t *connection = xcb_connect(NULL, &screen_num);*/

        /*const xcb_setup_t *setup = xcb_get_setup(connection);*/
        /*xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);*/

        /*for (i = 0; i < screen_num; i++) {*/
                /*xcb_screen_next(&iter);*/
        /*}*/

        /*xcb_screen_t *screen = iter.data;*/

        /*printf("\n");*/
        /*printf("Information about screen %"PRIu32":\n", screen->root);*/
        /*printf("  width         : %"PRIu16"\n", screen->width_in_pixels);*/
        /*printf("  height        : %"PRIu16"\n", screen->height_in_pixels);*/
        /*printf("  white pixel   : %"PRIu32"\n", screen->white_pixel);*/
        /*printf("  black pixel   : %"PRIu32"\n", screen->black_pixel);*/

        /*xcb_disconnect(connection);*/
        return 0;
}
