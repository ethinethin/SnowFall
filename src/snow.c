#include <SDL2/SDL.h>
#include "main.h"
#include "rand.h"
#include "snow.h"

#define NUM_FLAKES 1000

/* Function prototypes */
static void	draw_point(struct game *cur_game, int x, int y);

struct snowflake {
	int x;
	int y;
	int dx;
	int dy;
	int count;
};

struct snowflake *ALL_FLAKES = NULL;

void
init_snowflakes(struct game *cur_game)
{
	ALL_FLAKES = malloc(sizeof(*ALL_FLAKES) * NUM_FLAKES);
	int i;
	int rando;
	for (i = 0; i < NUM_FLAKES; i += 1) {
		ALL_FLAKES[i].x = rand_num(0, cur_game->display.w);
		ALL_FLAKES[i].y = rand_num(0, cur_game->display.h);
		rando = rand_num(0, 99);
		if (rando <= 49) {
			ALL_FLAKES[i].dx = -1;
		} else {
			ALL_FLAKES[i].dx = 1;
		}
		ALL_FLAKES[i].dy = rand_num(2, 4);
		ALL_FLAKES[i].count = rand_num(0, 49);
	}
}

void
kill_snowflakes(void)
{
	free(ALL_FLAKES);
}

void
change_snowflakes(struct game *cur_game)
{
	int i;
	
	for (i = 0; i < NUM_FLAKES; i += 1) {
		/* Change coordinates */
		ALL_FLAKES[i].x += ALL_FLAKES[i].dx;
		ALL_FLAKES[i].y += ALL_FLAKES[i].dy;
		/* Did it fall off the screen? */
		if (ALL_FLAKES[i].y > cur_game->display.h) {
			ALL_FLAKES[i].y = -10;
		}
		/* Change count and change dx if necessary */
		ALL_FLAKES[i].count -= 1;
		if (ALL_FLAKES[i].count < 0) {
			ALL_FLAKES[i].count = 49;
			ALL_FLAKES[i].dx *= -1;
		}
	}
}

void
draw_snowflakes(struct game *cur_game)
{
	int i;
	
	SDL_SetRenderDrawColor(cur_game->display.renderer, 0, 0, 0, 255);
	SDL_RenderClear(cur_game->display.renderer);
	for (i = 0; i < NUM_FLAKES; i += 1) {
		/* Draw */
		draw_point(cur_game, ALL_FLAKES[i].x, ALL_FLAKES[i].y);
	}
	SDL_RenderPresent(cur_game->display.renderer);
}

static void
draw_point(struct game *cur_game, int x, int y)
{
	SDL_SetRenderDrawColor(cur_game->display.renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(cur_game->display.renderer, x, y);
	SDL_RenderDrawPoint(cur_game->display.renderer, x + 1, y);
	SDL_RenderDrawPoint(cur_game->display.renderer, x - 1, y);
	SDL_RenderDrawPoint(cur_game->display.renderer, x, y + 1);
	SDL_RenderDrawPoint(cur_game->display.renderer, x, y - 1);
}
