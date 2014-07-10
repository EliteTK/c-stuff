#include <unistd.h>
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

        xcb_segment_t segments[] {
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

        const xcb_setup_t *setup = xcb_get_setup(connection);
        xcb_screen_t *screen = xcb_setup_roots_iterator(setup).data;

        xcb_drawable_t window = screen->root;
        xcb_gcontext_t foreground = xcb_generate_id(connection);
        uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
        uint32_t values[2] = {
                screen->black_pixel,
                0
        };

        xcb_create_gc(connection, foreground, window, mask, values);

        mask = XCB_CW_BLACK_PIXEL | XCB_CW_EVENT_MASK;
        values = {
                screen->white_pixel,


        xcb_window_t window = xcb_generate_id(connection);
        xcb_create_window(connection,
                        XCB_COPY_FROM_PARENT,
                        window,
                        screen->root,
                        0, 0,
                        150, 150,
                        10,
                        XCB_WINDOW_CLASS_INPUT_OUTPUT,
                        screen->root_visual,
                        0, NULL);

        xcb_map_window(connection, window);

        xcb_flush(connection);

        pause();

        xcb_disconnect(connection);

        return 0;
}
