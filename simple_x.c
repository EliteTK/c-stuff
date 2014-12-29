/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
/* SimplX - Proposed name if not taken already. */
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

/*
 * TODO: Figure out the alignment of these things fix the arrangement.
 *       Find a good name for this.
 */
typedef struct sx_gc {
	/*struct {*/
	xcb_connection_t *connection;
	xcb_screen_t *screen;
	xcb_drawable_t window;
	xcb_pixmap_t pixmap;
	xcb_image_t *image;
	xcb_gcontext_t gc;
	/*} xcb;*/
} SX;

SX *sx_new_gc(uint16_t width, uint16_t height)
{
	SX *sx = malloc(sizeof(SX));

	sx->connection = xcb_connect(NULL, NULL);

	sx->screen = xcb_setup_roots_iterator(xcb_get_setup(sx->connection)).data;

	uint32_t mask = XCB_CW_BACK_PIXEL; /* Needs events */
	uint32_t values[] = {sx->screen->black_pixel};

	sx->window = xcb_generate_id(sx->connection);
	xcb_create_window(sx->connection,
			24,
			sx->window,
			sx->screen->root,
			0, 0,
			width, height,
			1,
			XCB_WINDOW_CLASS_INPUT_OUTPUT,
			sx->screen->root_visual,
			mask, values);

	sx->pixmap = xcb_generate_id(sx->connection);
	xcb_create_pixmap(sx->connection,
			24,
			sx->pixmap,
			sx->window,
			width, height);

	uint8_t *img = malloc(width * height * 4);
	xcb_image_t *image = xcb_image_create(width, height,
			XCB_IMAGE_FORMAT_Z_PIXMAP,
			8, 24, 32,
			0,
			XCB_IMAGE_ORDER_MSB_FIRST,
			XCB_IMAGE_ORDER_LSB_FIRST,
			img,
			width * height * 4,
			img);

	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
	values[0] = sx->screen->black_pixel;
	values[1] = 0xFFFFFF;

	sx->gc = xcb_generate_id(sx->connection);
	xcb_create_gc(sx->connection,
			sx->gc,
			sx->pixmap,
			mask, values);

	return sx;
}
