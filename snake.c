#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

enum colorpair {
	C_BLANK = 1,
	C_WALL,
	C_SEGMENT0,
	C_SEGMENT1,
	C_APPLE
};

enum direction {
	D_UP,
	D_DOWN,
	D_LEFT,
	D_RIGHT
};

enum state {
	S_NORMAL,
	S_WON,
	S_FAIL
};

struct segment {
	uint32_t x, y;
};

struct snake {
	struct segment segments[UINT16_MAX];
	uint16_t head, tail;
	enum direction direction;
} snake;

struct apple {
	uint32_t x, y;
};

struct {
	struct snake snake;
	struct apple apple;
	uint32_t width, height;
	bool running;
	enum state state;
} game;

void init_ncurses(void)
{
	initscr();
	cbreak();
	noecho();
	nonl();
	start_color();

	intrflush(stdscr, FALSE);
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	init_pair(C_BLANK, COLOR_BLACK, COLOR_BLACK);
	init_pair(C_WALL, COLOR_WHITE, COLOR_WHITE);
	init_pair(C_SEGMENT0, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(C_SEGMENT1, COLOR_GREEN, COLOR_GREEN);
	init_pair(C_APPLE, COLOR_RED, COLOR_RED);

	bkgd(COLOR_PAIR(C_BLANK));
}

void init_game(void)
{
	game.running = true;
	game.state = S_NORMAL;

	game.snake.direction = D_UP;

	getmaxyx(stdscr, game.height, game.width);

	game.snake.head = 1;
	game.snake.tail = 0;

	game.snake.segments[game.snake.tail].x = game.width / 2;
	game.snake.segments[game.snake.tail].y = game.height / 2;

	game.snake.segments[game.snake.head].x = game.width / 2;
	game.snake.segments[game.snake.head].y = game.height / 2 - 1;

	game.apple.x = game.width / 2;
	game.apple.y = game.height / 2 + 1;
}

void print_board(void)
{
	erase();

	for (uint16_t i = game.snake.tail; i <= game.snake.head; i++) {
		chtype ch;

		if (i % 2)
			ch = ACS_BLOCK | COLOR_PAIR(C_SEGMENT0);
		else
			ch = ACS_BLOCK | COLOR_PAIR(C_SEGMENT1);
		mvaddch(game.snake.segments[i].y, game.snake.segments[i].x, ch);
	}


	mvaddch(game.apple.y, game.apple.x, ACS_BLOCK | COLOR_PAIR(C_APPLE));

	refresh();
}

void redirect(enum direction desired_dir)
{
	struct segment *current = &game.snake.segments[game.snake.head];
	struct segment *previous = &game.snake.segments[game.snake.head - 1];

	if (desired_dir == game.snake.direction)
		return;

	if (current->x == previous->x)
		if (current->y > previous->y) {
			if (desired_dir == D_UP)
				return;
		} else {
			if (desired_dir == D_DOWN)
				return;
		}
	else if (current->y == previous->y)
		if (current->x > previous->x) {
			if (desired_dir == D_LEFT)
				return;
		} else {
			if (desired_dir == D_RIGHT)
				return;
		}

	game.snake.direction = desired_dir;
}

void poll_input(void)
{
	int c;

	while ((c = getch()) != ERR)
		switch (c) {
		case 'h': redirect(D_LEFT); break;
		case 'j': redirect(D_DOWN); break;
		case 'k': redirect(D_UP); break;
		case 'l': redirect(D_RIGHT); break;
		case 'q': game.running = false; break;
		}
}

inline uint16_t rand_to_max(uint16_t max)
{
	double random;

	while ((random = rand()) == (double)RAND_MAX);
	return random / (double)RAND_MAX * (double)max;
}

bool part_of_snake(uint16_t x, uint16_t y)
{
	for (uint16_t i = game.snake.tail; i != game.snake.head; i++)
		if (game.snake.segments[i].x == x && game.snake.segments[i].y == y)
			return true;

	return false;
}

void replace_apple(void)
{
	uint16_t x, y;

	while (true) {
		x = rand_to_max(game.width);
		y = rand_to_max(game.height);

		if (part_of_snake(x, y))
			continue;

		game.apple.x = x;
		game.apple.y = y;

		break;
	}
}

void simulate(void)
{
	struct segment *current = &game.snake.segments[game.snake.head];
	int64_t dx = 0, dy = 0, nx, ny;

	switch (game.snake.direction) {
	case D_UP: dy = -1; break;
	case D_DOWN: dy = 1; break;
	case D_LEFT: dx = -1; break;
	case D_RIGHT: dx = 1; break;
	}

	nx = (int64_t)current->x + dx;
	ny = (int64_t)current->y + dy;

	if (nx < 0 || nx >= game.width || ny < 0 || ny >= game.height) {
		game.running = false;
		game.state = S_FAIL;
		return;
	}

	if (nx == game.apple.x && ny == game.apple.y) {
		game.snake.head++;
		game.snake.segments[game.snake.head].x = nx;
		game.snake.segments[game.snake.head].y = ny;

		replace_apple();
		return;
	}

	if (part_of_snake(nx, ny)) {
		game.running = false;
		game.state = S_FAIL;
		return;
	}

	game.snake.head++;
	game.snake.segments[game.snake.head].x = nx;
	game.snake.segments[game.snake.head].y = ny;
	game.snake.tail++;
}

void main_loop(void)
{
	while (true) {
		poll_input();
		if (!game.running)
			break;
		simulate();
		if (!game.running)
			break;
		print_board();
		usleep(100000);
	}
}

int main(void)
{
	init_ncurses();
	init_game();
	main_loop();

	return EXIT_SUCCESS;
}
