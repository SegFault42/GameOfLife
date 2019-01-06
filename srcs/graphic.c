#include "graphic.h"
#include "draw.h"

/*void	main_menu(win_render *w_rend)*/
/*{*/
	/*draw_entry(w_rend);*/
/*}*/

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
		draw_grill(w_rend->renderer, square_size);

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
			SDL_Delay(200);
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
		draw_entry(w_rend->renderer, 100, 100, "Hello");
	}
}
