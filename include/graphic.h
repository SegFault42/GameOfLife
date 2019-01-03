#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "common.h"

win_render	*graphic();
void	draw_grill(win_render *w_rend, int grid_gap);
void	draw_rectangle(SDL_Renderer	*renderer, int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
void	create_map(bool old_tab[][NB_LINE], win_render *w_rend);

#endif
