#ifndef DRAW_H
#define DRAW_H

void	draw_entry(SDL_Renderer *renderer, int x, int y, char *str);
void	draw_grill(SDL_Renderer	*renderer, int grid_gap);
void	create_rectangle(SDL_Rect *rectangle, int x, int y, int width, int height);
void	draw_rectangle(SDL_Renderer	*renderer, int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

#endif
