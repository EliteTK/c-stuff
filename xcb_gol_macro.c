/*
 * Copyright (C) 2014  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

#define BOARD_WIDTH 500
#define BOARD_HEIGHT 500

#define PIXEL 1

#define WIDTH (BOARD_WIDTH * PIXEL)
#define HEIGHT (BOARD_HEIGHT * PIXEL)

#define GOL_CLAMP(pos, max) ((pos) < 0 ? (pos) + (max) : (pos) % (max))
#define GOL_CLAMPX(gol, pos) (GOL_CLAMP((pos), (gol)->width))
#define GOL_CLAMPY(gol, pos) (GOL_CLAMP((pos), (gol)->height))
#define GOL_RESOLVE_F(gol, x, y) ((gol)->buffers[(gol)->front][(GOL_CLAMPX(gol, x))\
		+ (GOL_CLAMPY(gol, y)) * (gol)->width])
#define GOL_RESOLVE_B(gol, x, y) ((gol)->buffers[!(gol)->front][(GOL_CLAMPX(gol, x))\
		+ (GOL_CLAMPY(gol, y)) * (gol)->width])

typedef struct gol_t {
	uint32_t width, height;
	bool *buffers[2];
	uint8_t front;
} Gol;

Gol *gol_new(unsigned const int width, unsigned const int height)
{
	Gol *gol = malloc(sizeof(Gol));
	gol->width = width;
	gol->height = height;
	gol->front = 0;
	gol->buffers[0] = malloc(width * height * sizeof(bool));
	gol->buffers[1] = malloc(width * height * sizeof(bool));
	return gol;
}

void gol_del(Gol *gol)
{
	free(gol->buffers[0]);
	free(gol->buffers[1]);
	free(gol);
}

void gol_random(Gol *const gol, unsigned const int seed)
{
	srand(seed);
	for (uint32_t i = 0; i < gol->width * gol->height; i++)
		gol->buffers[gol->front][i] = rand() < 0.5 * ((double)RAND_MAX + 1.0);
}

static uint8_t gol_neighbours(Gol *const gol, const int32_t x, const int32_t y)
{
	uint8_t neighbours = 0;
	for (int8_t dx = -1; dx <= 1; dx++)
		for (int8_t dy = -1; dy <= 1; dy++)
			if (!(dx == 0 && dy == 0) && GOL_RESOLVE_F(gol, x + dx, y + dy))
				neighbours++;
	return neighbours;
}

void gol_simulate(Gol *const gol)
{
	for (uint32_t x = 0; x < gol->width; x++)
		for (uint32_t y = 0; y < gol->height; y++) {
			uint8_t neighbours = gol_neighbours(gol, x, y);
			if (GOL_RESOLVE_F(gol, x, y)){
				if (neighbours < 2)
					GOL_RESOLVE_B(gol, x, y) = 0;
				else if (neighbours <= 3)
					GOL_RESOLVE_B(gol, x, y) = 1;
				else
					GOL_RESOLVE_B(gol, x, y) = 0;
			} else {
				if (neighbours == 3)
					GOL_RESOLVE_B(gol, x, y) = 1;
				else
					GOL_RESOLVE_B(gol, x, y) = 0;
			}
		}

	gol->front = !gol->front;
}

int main(int argc, char **argv)
{
	xcb_connection_t *connection = xcb_connect(NULL, NULL);

	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	uint32_t mask = XCB_CW_BACK_PIXEL;
	uint32_t values[] = {screen->black_pixel};

	xcb_drawable_t window = xcb_generate_id(connection);
	xcb_create_window(connection,
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

	uint8_t *img = malloc(WIDTH * HEIGHT * 4);
	xcb_image_t *image = xcb_image_create(WIDTH, HEIGHT,
			XCB_IMAGE_FORMAT_Z_PIXMAP,
			8, 24, 32,
			0,
			XCB_IMAGE_ORDER_MSB_FIRST,
			XCB_IMAGE_ORDER_LSB_FIRST,
			img,
			WIDTH * HEIGHT * 4,
			img);

	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
	values[0] = screen->black_pixel;
	values[1] = 0xFFFFFF;

	xcb_gcontext_t gc = xcb_generate_id(connection);
	xcb_create_gc(connection,
			gc,
			pixmap,
			mask, values);

	xcb_image_put(connection, pixmap, gc, image, 0, 0, 0);

	xcb_map_window(connection, window);
	xcb_flush(connection);

	uint8_t value = 0;

	uint32_t *limg;

	Gol *gol = gol_new(BOARD_WIDTH, BOARD_HEIGHT);
	gol_random(gol, time(NULL));

	while (1) {
		limg = (uint32_t *)image->data;

		for (int i = 0; i < BOARD_WIDTH * BOARD_HEIGHT; i++)
			*(limg++) = gol->buffers[gol->front][i] ? 0x00FFFF00 : 0x00000000;

		xcb_image_put(connection, pixmap, gc, image, 0, 0, 0);

		xcb_copy_area(connection,
				pixmap,
				window,
				gc,
				0, 0,
				0, 0,
				WIDTH, HEIGHT);
		xcb_flush(connection);
		value++;

		gol_simulate(gol);
	}
	return 0;
}
