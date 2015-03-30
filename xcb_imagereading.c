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
#include <xcb/xcb_image.h>
#include <xif.h>

#define WIDTH 640
#define HEIGHT 480

int main(int arg, char **argv)
{
	xcb_connection_t *connection = xcb_connect(NULL, NULL);

	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	xcb_colormap_t colormap = screen->default_colormap;

	xcb_drawable_t window = xcb_generate_id(connection);
	uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[] = {screen->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_BUTTON_PRESS};
	xcb_create_window(connection,
			/*screen->root_depth,*/
			24,
			window,
			screen->root,
			0, 0,
			WIDTH, HEIGHT,
			1,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			screen->root_visual,
			mask, values);

	xcb_pixmap_t pixmap = xcb_generate_id(connection);
	xcb_create_pixmap(connection,
			24,
			pixmap,
			window,
			WIDTH, HEIGHT);
	xcb_image_t *image;
	if (!(image = xif_read("test.xif"))) {
		fputs("Error: xif_read returned null.\n", stderr);
		exit(1);
	}

	xcb_gcontext_t gc = xcb_generate_id(connection);
	xcb_create_gc(connection,
			gc,
			pixmap,
			0, NULL);

	xcb_image_put(connection, pixmap, gc, image, 0, 0, 0);

	xcb_map_window(connection, window);
	xcb_flush(connection);

	xcb_generic_event_t *event;
	while ((event = xcb_wait_for_event(connection))) {
		switch (event->response_type & ~0x80) {
			case XCB_EXPOSE:
			{
				xcb_expose_event_t *expose = (xcb_expose_event_t *)event;
				xcb_copy_area(connection,
						pixmap,
						window,
						gc,
						expose->x, expose->y,
						expose->x, expose->y,
						expose->width, expose->height);
				xcb_flush(connection);
				break;
			}
			case XCB_BUTTON_PRESS:
					goto end;
					break;
			default:
					break;
		}
		free(event);
	}
end:

	xcb_free_pixmap(connection, pixmap);
	xcb_disconnect(connection);

	xcb_image_destroy(image);

	return 0;
}
