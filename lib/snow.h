#ifndef SNOW_H
#define SNOW_H

#include "main.h"

extern void	init_snowflakes(struct game *cur_game, int num_flakes, int hor_speed, int ver_speed);
extern void	kill_snowflakes(void);
extern void	change_snowflakes(struct game *cur_game);
extern void	draw_snowflakes(struct game *cur_game);

#endif
