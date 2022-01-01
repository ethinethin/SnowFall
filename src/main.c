#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "main.h"
#include "rand.h"
#include "snow.h"

/* Function prototypes */
void	init_disp(struct game *cur_game);
void	kill_disp(struct game *cur_game);

int
main(int argc, char *argv[])
{
	SDL_Event event;
	struct game cur_game = {
		{1280,			/* display.w */
		720,			/* display.h */
		"snowfall",		/* display.name */
		NULL,			/* display.window */
		NULL},			/* display.renderer */
		SDL_FALSE		/* running */
	};
	/* initialize snowflakes */
	seed_rng();
	if (argc == 4) {
		init_snowflakes(&cur_game, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	} else if (argc == 6) {
		cur_game.display.w = atoi(argv[4]);
		cur_game.display.h = atoi(argv[5]);
		init_snowflakes(&cur_game, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	} else if (argc == 1) {
		init_snowflakes(&cur_game, 0, 0, 0);
	} else {
		printf("Usage:\n\t%s [number flakes] [horizontal speed] [vertical speed]\n", argv[0]);
		printf("\t%s [number flakes] [horizontal speed] [vertical speed] [width] [height]\n", argv[0]);
		exit(1);
	}
	/* Initialize SDL, seed rng, and initialize display */
	SDL_Init(SDL_INIT_EVERYTHING);
	init_disp(&cur_game);
	/* Enter main loop */
	while (cur_game.running == SDL_TRUE) {
		/* Change and draw snowflakes */
		change_snowflakes(&cur_game);
		draw_snowflakes(&cur_game);
		SDL_Delay(10);
		if (SDL_PollEvent(&event) == 0) continue;
		if (event.type == SDL_QUIT) {
			cur_game.running = SDL_FALSE;
		} else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE:
				cur_game.running = SDL_FALSE;
				break;
			}
		}
	}
	/* Destroy snowflakes, display, and exit */
	kill_snowflakes();
	kill_disp(&cur_game);
	SDL_Quit();
	return 0;
}

void
init_disp(struct game *cur_game)
{
	SDL_Event event;
	
	cur_game->display.window = SDL_CreateWindow(cur_game->display.name, 0, 0, cur_game->display.w, cur_game->display.h, SDL_WINDOW_SHOWN);
	cur_game->display.renderer = SDL_CreateRenderer(cur_game->display.window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_TARGETTEXTURE|SDL_RENDERER_PRESENTVSYNC);
	// You may want this
	//SDL_SetRenderDrawBlendMode(cur_game->display.renderer, SDL_BLENDMODE_BLEND);
	/* Create output texture */
	/* Poll for an event and wait 100ms - bring the window to the foreground */
	SDL_PollEvent(&event);
	SDL_Delay(100);
	/* Game is running */
	cur_game->running = SDL_TRUE;
}

void
kill_disp(struct game *cur_game)
{
	/* Delay to prevent segfaults in other thread loops */
	SDL_Delay(100);
	SDL_DestroyRenderer(cur_game->display.renderer);
	SDL_DestroyWindow(cur_game->display.window);
}
