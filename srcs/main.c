#include "common.h"
#include "graphic.h"
#include "gameoflife.h"
#include "nxui.h"

int	square_size = 5;

int	main(void)
{
	NXUI_graphic	*graphic = NULL;

	// Setup SDL
	graphic = NXUI_init();
	if (graphic == NULL) {
		fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
		return (-1);
	}

	NXUI_layout1(graphic->renderer, "Game of life");
	SDL_RenderPresent(graphic->renderer);
	// start game
	while (true)
	{}
		/*main_menu(graphic);*/
		/*game_of_life(graphic);*/


	NXUI_de_init(graphic);
}
