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

void	draw_rectangle(SDL_Renderer	*renderer, int x, int y)
{
		SDL_Rect	rectangle;

		// -1 and +1 to fit perfectly in square
		rectangle.w = SQUARE_SIZE - 1;
		rectangle.h = SQUARE_SIZE - 1;
		rectangle.x = x + 1;
		rectangle.y = y + 1;

		if (rectangle.y < NB_COLUMN * SQUARE_SIZE && rectangle.x < NB_LINE * SQUARE_SIZE) {
			SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
			SDL_RenderFillRect(renderer, &rectangle);
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

	printf("nb_column = %d, nb_lines = %d, middle_y = %d, middle_x = %d\n", NB_COLUMN, NB_LINE, MIDDLE_Y, MIDDLE_X);

	while (true) {
		// Clear screen
		SDL_SetRenderDrawColor(w_rend->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(w_rend->renderer);

		// Draw grill
		draw_grill(w_rend, SQUARE_SIZE);

		//Game of life
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (new_tab[y][x] == 'o')
					draw_rectangle(w_rend->renderer, x * SQUARE_SIZE, y * SQUARE_SIZE);
			}
		}

		// check cells and refresh
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (dead_or_alive(old_tab, x, y) == true)
					new_tab[y][x] = CELL_ALIVE;
				else
					new_tab[y][x] = CELL_DEAD;
			}
		}

		// update old tab
		memcpy(old_tab, new_tab, sizeof(old_tab));

		// Render to screen
		SDL_RenderPresent(w_rend->renderer);
		SDL_Delay(50);
	}
}
