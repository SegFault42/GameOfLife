#include "common.h"
#include "graphic.h"
#include "gameoflife.h"

int	square_size = 5;

int	main(void)
{
	win_render	*w_rend = NULL;

	// Setup SDL
	w_rend = graphic();
	if (w_rend == NULL)
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());

	// start game
	while (true)
		game_of_life(w_rend);

}
