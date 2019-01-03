#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#include "common.h"

uint8_t	rule(bool tab[][NB_LINE], const int x, const int y);
bool	dead_or_alive(bool tab[][NB_LINE], const int x, const int y);
void	game_of_life(win_render *w_rend);

#endif
