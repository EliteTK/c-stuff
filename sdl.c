#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 640
#define HEIGHT 480
#define DEPTH 32

enum obj_type {
	O_QUAD,
	O_TRIG,
	O_CIRC
};

struct quad {
	uint32_t x, y, width, height;
};

struct circle {
	uint32_t x, y, diameter;
};

typedef union colour_t {
	struct {
		uint8_t a, r, g, b;
	} comp;
	uint32_t colour;
} colour_t;

struct object {
	enum obj_type type;
	colour_t colour;
	union {
		struct quad quad;
		struct circle circle;
	} obj;
};

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *screen;
colour_t *buffer;

struct object *objects;
uint32_t object_count;

volatile bool running = true;

#define QUOTE(text) "`" #text "'"
#define SDL_ASSERT(expr, comp, val) \
	if ((expr) comp val) { \
		fprintf(stderr, "SDL Error: %s - %s\n", QUOTE(expr), SDL_GetError()); \
		exit(EXIT_FAILURE); \
	}

#define SDL_ASSERT_NN(expr) SDL_ASSERT(expr, ==, NULL)
#define SDL_ASSERT_Z(expr) SDL_ASSERT(expr, !=, 0)

void prep_objects()
{
	objects = malloc(1 * sizeof *objects);
	objects[0] = (struct object){O_QUAD, {{255, 0, 0, 0}}, {.quad = {30, 30, 30, 30}}};

	object_count = 1;
}

void draw_screen()
{
	for (size_t i = 0; i < WIDTH * HEIGHT; i++)
		buffer[i] = (colour_t){{0, 255, 0, 0}};

	SDL_UpdateTexture(screen, NULL, buffer, 640 * sizeof *buffer);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, screen, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void poll_for_events()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit(EXIT_SUCCESS);
			break;
		case SDL_KEYDOWN:
			printf("Key.\n");
			break;
		}
	}
}

void simulate(uint32_t difference)
{
	printf("%lu\n", difference);
}

uint32_t get_time_delta()
{
	static uint32_t old_time;
	uint32_t time = SDL_GetTicks();
	uint32_t difference = time - old_time;
	old_time = time;
	return difference;
}

int main(void)
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	atexit(SDL_Quit);

	window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	renderer = SDL_CreateRenderer(window, -1, 0);
	screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 640, 480);
	buffer = malloc(sizeof *buffer * 640 * 480);

	prep_objects();

	get_time_delta();

	while (running) {
		draw_screen();
		poll_for_events();
		simulate(get_time_delta());
	}

	return(EXIT_SUCCESS);
}
