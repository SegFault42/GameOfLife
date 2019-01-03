#include "common.h"
#include "gameoflife.h"
#include "graphic.h"

uint8_t	rule(bool tab[][NB_LINE], const int x, const int y)
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

bool	dead_or_alive(bool tab[][NB_LINE], const int x, const int y)
{
	uint8_t	alive = 0;

	alive = rule(tab, x, y);

	// exec rule 1
	if (tab[y][x] == CELL_ALIVE && (alive == 2 || alive == 3))
		return (true);
	// exec rule 2
	if (tab[y][x] == CELL_DEAD && alive == 3)
		return (true);

	return (false);
}

void	game_of_life(win_render *w_rend)
{
	bool		old_tab[NB_COLUMN][NB_LINE];
	bool		new_tab[NB_COLUMN][NB_LINE];

	// Init all tab with '.' (DEAD CELL)
	memset(old_tab, false, sizeof(old_tab));

	create_map(old_tab, w_rend);

	memcpy(new_tab, old_tab, sizeof(new_tab));

	// Laucnh game of life
	while (true) {
		hidScanInput();

		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS)
			break ;
		else if (kHeld & KEY_L && square_size > 2) {
			--square_size;
		}
		else if (kHeld & KEY_R && square_size < 100) {
			++square_size;
		}

		// Clear screen
		SDL_SetRenderDrawColor(w_rend->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(w_rend->renderer);

		// Draw grill
		draw_grill(w_rend, square_size);

		//Game of life
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (new_tab[y][x] == CELL_ALIVE)
					draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0xff, 0, 0, 0);
			}
		}

		// check cells and refresh
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (dead_or_alive(old_tab, x, y) == CELL_ALIVE)
					new_tab[y][x] = CELL_ALIVE;
				else
					new_tab[y][x] = CELL_DEAD;
			}
		}

		// update old tab
		memcpy(old_tab, new_tab, sizeof(old_tab));

		// Render to screen
		SDL_RenderPresent(w_rend->renderer);
		SDL_Delay(60);
	}
}

