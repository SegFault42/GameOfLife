#include "./include/common.h"

static uint8_t	rule(char tab[][NB_LINE], const int x, const int y)
{
	uint8_t	alive = 0;

	// Count number neighbors alive
	if (CHECK_X_PLUS && tab[y][x + 1] == CELL_ALIVE) { alive++; }
	if (CHECK_X_MIN && tab[y][x - 1] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_MIN && tab[y - 1][x] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_PLUS && tab[y + 1][x] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_MIN && CHECK_X_MIN && tab[y - 1][x - 1] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_PLUS && CHECK_X_MIN && tab[y + 1][x - 1] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_MIN && CHECK_X_PLUS && tab[y - 1][x + 1] == CELL_ALIVE) { alive++; }
	if (CHECK_Y_PLUS && CHECK_X_PLUS && tab[y + 1][x + 1] == CELL_ALIVE) { alive++; }

	return (alive);
}

static bool	dead_or_alive(char tab[][NB_LINE], const int x, const int y)
{
	uint8_t alive = 0;

	alive = rule(tab, x, y);

	// exec rule 1
	if (tab[y][x] == CELL_ALIVE && (alive == 2 || alive == 3))
		return (true);
	// exec rule 2
	if (tab[y][x] == CELL_DEAD && alive == 3)
		return (true);

	return (false);
}

static void	init_tab(char old_tab[NB_COLUMN][NB_LINE])
{
	old_tab[MIDDLE_Y][MIDDLE_X] = CELL_ALIVE;
	old_tab[MIDDLE_Y][MIDDLE_X + 1] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 1][MIDDLE_X - 1] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 1][MIDDLE_X] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 2][MIDDLE_X] = CELL_ALIVE;

	old_tab[3][3] = CELL_ALIVE;
	old_tab[3][4] = CELL_ALIVE;
	old_tab[3][5] = CELL_ALIVE;
}

typedef struct		win_render
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					win_render;

static win_render	*graphic()
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

static void	draw_grill(win_render *w_rend, int grid_gap)
{
	/*// Draw vertical lines*/
	for (int x = 0; x < WIN_WIDTH; x += grid_gap) {
		SDL_RenderDrawLine(w_rend->renderer, x, 0, x, WIN_HEIGHT);
	}

	// Draw horizontal lines
	for (int y = 0; y < WIN_HEIGHT; y += grid_gap) {
		SDL_RenderDrawLine(w_rend->renderer, 0, y, WIN_WIDTH, y);
	}
}

int	main()
{
	char		old_tab[NB_COLUMN][NB_LINE];
	char		new_tab[NB_COLUMN][NB_LINE];
	win_render	*w_rend = NULL;

	w_rend = graphic();
	if (w_rend == NULL)
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());

	// Init all tab with '.'
	memset(old_tab, CELL_DEAD, sizeof(old_tab));

	// draw cells
	init_tab(old_tab);

	memcpy(new_tab, old_tab, sizeof(new_tab));

	while (true) {
		/*SDL_Rect	rectangle;*/

		/*rectangle.x = 500;*/
		/*rectangle.y = 500;*/
		/*rectangle.w = 50;*/
		/*rectangle.h = 50;*/

		/*SDL_RenderFillRect(w_rend->renderer, &rectangle);*/
		/*SDL_RenderPresent(w_rend->renderer);*/

		// Draw pixel in red
		SDL_SetRenderDrawColor(w_rend->renderer, 0xFF, 0, 0, 0xFF);

		SDL_RenderDrawPoint(w_rend->renderer, 20, 20);

		draw_grill(w_rend, 5);

		SDL_RenderPresent(w_rend->renderer);
	}

	/*while (0x1) {*/
		/*CLEAR();*/
		/*printf("\x1b[0;0H");*/

		/*// Print map*/
		/*for (int y = 0; y < NB_COLUMN; y++) {*/
			/*for (int x = 0; x < NB_LINE; x++) {*/
				/*draw_rect(w_rend, y, x, new_tab[y][x]);*/
				/*printf("%c", new_tab[y][x]);*/
			/*}*/
			/*printf("\n");*/
		/*}*/

		/*// check cells and refresh*/
		/*for (int y = 0; y < NB_COLUMN; y++) {*/
			/*for (int x = 0; x < NB_LINE; x++) {*/
				/*if (dead_or_alive(old_tab, x, y) == true)*/
					/*new_tab[y][x] = CELL_ALIVE;*/
				/*else*/
					/*new_tab[y][x] = CELL_DEAD;*/
			/*}*/
		/*}*/

		/*// update old tab*/
		/*memcpy(old_tab, new_tab, sizeof(old_tab));*/

		/*usleep(80000);*/
		/*printf("\n");*/
	/*}*/
}
