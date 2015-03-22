/*
 * A simple implementation of the snake game.
 * Compile with: `make LDLIBS=-lncurses snake'
 *
 * Copyright (C) 2015  Tomasz Kramkowski <tk@the-tk.com>
 *
 * This program is free software. It is licensed under version 3 of the
 * GNU General Public License.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see [http://www.gnu.org/licenses/].
 */
#include <argp.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define USEC_SECOND 1000000

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
};

struct apple {
	uint32_t x, y;
};

struct {
	struct snake snake;
	struct apple apple;
	uint32_t width, height;
	bool running;
	enum state state;
	bool alternate_color;
} game;

struct arguments {
	useconds_t delay;
	uint16_t desired_width, desired_height;
	bool alternate_color;
} arguments;

const char *argp_program_version = "1.0rc1";
const char *argp_program_bug_address = "<snake@the-tk.com>";

void init_ncurses(void)
{
	cbreak();
	initscr();
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

		if ((i - game.snake.head * !arguments.alternate_color) % 2)
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

inline bool part_of_snake(uint16_t x, uint16_t y)
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
	struct segment *head = &game.snake.segments[game.snake.head];
	struct segment *tail = &game.snake.segments[game.snake.tail];
	int64_t dx = 0, dy = 0, nx, ny;

	switch (game.snake.direction) {
	case D_UP: dy = -1; break;
	case D_DOWN: dy = 1; break;
	case D_LEFT: dx = -1; break;
	case D_RIGHT: dx = 1; break;
	}

	nx = (int64_t)head->x + dx;
	ny = (int64_t)head->y + dy;

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

	if (part_of_snake(nx, ny) && !(tail->x == nx && tail->y == ny)) {
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
	print_board();
	poll_input();

	while (game.running) {
		usleep(arguments.delay);
		poll_input();
		simulate();
		print_board();
	}
}

error_t parse_arg(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key) {
	case 'w':
		fprintf(stderr, "Width setting is not yet implemented.\n");
		arguments->desired_width = strtol(arg, NULL, 10);
		break;
	case 'h':
		fprintf(stderr, "Height setting is not yet implemented.\n");
		arguments->desired_height = strtol(arg, NULL, 10);
		break;
	case 'a':
		arguments->alternate_color = true;
		break;
	case 'd':
		arguments->delay = strtod(arg, NULL) * (double)USEC_SECOND;
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

void parse_args(int argc, char **argv)
{
	char *doc = "An ncurses implementation of snake in c.";

	struct argp_option options[] = {
		{"width", 'w', "<width>", 0, "Desired width.", 0},
		{"height", 'h', "<height>", 0, "Desired height.", 0},
		{"alternate", 'a', NULL, 0, "Alternate snake colour.", 0},
		{"delay", 'd', "<seconds>", 0, "Delay between ticks in seconds. (default: 0.1)", 0},
		{0}
	};

	struct argp argp = {options, parse_arg, NULL, doc, NULL, NULL, NULL};

	arguments.desired_width = 0;
	arguments.desired_height = 0;
	arguments.alternate_color = false;
	arguments.delay = (double)USEC_SECOND * 0.1;

	argp_parse(&argp, argc, argv, 0, 0, &arguments);
}

int main(int argc, char **argv)
{
	parse_args(argc, argv);
	init_ncurses();
	init_game();

	main_loop();

	endwin();
	return EXIT_SUCCESS;
}
