#include "graphic.h"

win_render	*graphic()
{
	win_render	*w_rend = NULL;

	w_rend = (win_render *)malloc(sizeof(win_render));

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (w_rend);

	w_rend->window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

	if (w_rend->window == NULL)
		goto end;

	w_rend->renderer = SDL_CreateRenderer(w_rend->window, -1, SDL_RENDERER_ACCELERATED);
	if (w_rend->renderer == NULL) {
		fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
		goto end;
	}

	if (SDL_SetRenderDrawColor(w_rend->renderer, 0x00, 0x00, 0x00, 0x00)) {
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
		goto end;
	}

	if (SDL_RenderClear(w_rend->renderer) != 0) {
		fprintf(stderr, "Erreur SDL_RenderClear : %s", SDL_GetError());
		goto end;
	}

	/*SDL_Delay(5000);*/

	return (w_rend);

end:
	SDL_DestroyRenderer(w_rend->renderer);
	SDL_DestroyWindow(w_rend->window);
	SDL_Quit();
	return (w_rend);
}

void	draw_grill(win_render *w_rend, int grid_gap)
{
	// Draw grill in green
	SDL_SetRenderDrawColor(w_rend->renderer, 0x33, 0x33, 0, 0x33);

	/*// Draw vertical lines*/
	for (int x = 0; x < WIN_WIDTH; x += grid_gap) {
		SDL_RenderDrawLine(w_rend->renderer, x, 0, x, WIN_HEIGHT);
	}

	// Draw horizontal lines
	for (int y = 0; y < WIN_HEIGHT; y += grid_gap) {
		SDL_RenderDrawLine(w_rend->renderer, 0, y, WIN_WIDTH, y);
	}
}

void	draw_rectangle(SDL_Renderer	*renderer, int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
		SDL_Rect	rectangle;

		// -1 and +1 to fit perfectly in square
		rectangle.w = square_size - 1;
		rectangle.h = square_size - 1;
		rectangle.x = x + 1;
		rectangle.y = y + 1;

		if (rectangle.y < NB_COLUMN * square_size && rectangle.x < NB_LINE * square_size) {
			SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
			SDL_RenderFillRect(renderer, &rectangle);
		}
}

void	create_map(bool old_tab[][NB_LINE], win_render *w_rend)
{
	int	x = 0, y = 0;

	// Draw custom map
	while (true) {
		hidScanInput();

		u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		// quit map editor
		if (kDown & KEY_B)
			break ;

		// Clear screen
		SDL_SetRenderDrawColor(w_rend->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(w_rend->renderer);

		// Draw grill
		draw_grill(w_rend, square_size);

		//Capture input
		if (kHeld & KEY_RIGHT && x < NB_LINE) {
			x++;
		} else if (kHeld & KEY_LEFT && x > 0) {
			x--;
		} else if (kHeld & KEY_DOWN && y < NB_COLUMN) {
			y++;
		} else if (kHeld & KEY_UP && y > 0) {
			y--;
		} else if (kDown & KEY_A) {
			if (old_tab[y][x] == true)
				old_tab[y][x] = false;
			else
				old_tab[y][x] = true;
		} else if (kHeld & KEY_L && square_size > 5) {
			--square_size;
		} else if (kHeld & KEY_R && square_size < 100) {
			++square_size;
		}

		if (kHeld) {
			SDL_Delay(100);
		}

		// Draw cell on current postion
		if (old_tab[y][x] == CELL_ALIVE)
			draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0, 0xff, 0xff, 0xff);
		else
			draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0, 0xff, 0, 0xff);

		// Draw all cell
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (old_tab[y][x] == CELL_ALIVE)
					draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0xff, 0xff, 0, 0xff);
			}
		}

		// Render to screen
		SDL_RenderPresent(w_rend->renderer);
	}
}
