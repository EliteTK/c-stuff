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
#include <string.h>
#include <time.h>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

#define WIDTH 500
#define HEIGHT 500

#define ANT_BPOS(ant) ((ant)->buffer[(ant)->posy * (ant)->width + (ant)->posx])

enum ant_direction {
	NORTH,
	EAST,
	SOUTH,
	WEST
};

typedef struct ant {
	uint8_t *buffer;
	char *actions;
	uint16_t width, height;
	uint16_t posx,  posy;
	enum ant_direction direction;
} Ant;

Ant *ant_new(uint16_t width, uint16_t height, char *actions)
{
	Ant *ant = malloc(sizeof(Ant));

	ant->buffer = calloc(sizeof(uint8_t), width * height);

	ant->actions = strdup(actions);

	ant->width = width;
	ant->height = height;

	ant->posx = width / 2;
	ant->posy = width / 2;

	ant->direction = NORTH;

	return ant;
}

static void ant_del(Ant *ant)
{
	free(ant->buffer);
	free(ant->actions);
	free(ant);
}

static inline void ant_left(Ant *ant)
{
	ant->direction = ant->direction == 0 ? 3 : ant->direction - 1;
}

static inline void ant_right(Ant *ant)
{
	ant->direction = ant->direction == 3 ? 0 : ant->direction + 1;
}

static inline void ant_forward(Ant *ant)
{
	if (ant->direction & 1) { /* EAST or WEST */
		ant->posx = ant->direction == EAST ? ant->posx + 1 : ant->posx - 1;
	} else {
		ant->posy = ant->direction == SOUTH ? ant->posy + 1 : ant->posy - 1;
	}
}

void ant_simulate(Ant *ant)
{
	uint8_t act_current = ANT_BPOS(ant);
	uint8_t act_next = ant->actions[act_current + 1] != '\0' ? act_current + 1 : 0;

	if (ant->actions[act_current] == 'L') {
		ant_left(ant);
		ANT_BPOS(ant) = act_next;
		ant_forward(ant);
	} else {
		ant_right(ant);
		ANT_BPOS(ant) = act_next;
		ant_forward(ant);
	}

}

int main(int argc, char **argv)
{
	if (argc != 2) {
		printf("Usage: ant <action string>\n");
		exit(1);
	}

	xcb_connection_t *connection = xcb_connect(NULL, NULL);

	xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	uint32_t mask = XCB_CW_BACK_PIXEL;
	uint32_t values[2] = {screen->black_pixel};

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

	uint32_t step = 0;

	Ant *ant = ant_new(WIDTH, HEIGHT, argv[1]);
	putchar('\n');

	while (1) {
		printf("\rStep: %d", step++);
		fflush(stdout);
		limg = (uint32_t *)image->data;

		for (int i = 0; i < WIDTH * HEIGHT; i++) {
			uint32_t colour = 0;

			colour |= (ant->buffer[i] & 1) * 0xFF << 0;
			colour |= (ant->buffer[i] >> 1) * 0xFF << 8;
			colour |= (ant->buffer[i] >> 2) * 0xFF << 16;

			*(limg++) = colour;
		}

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

		ant_simulate(ant);
	}

	ant_del(ant);
	return 0;
}
