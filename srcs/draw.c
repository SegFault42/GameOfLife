#include "common.h"
#include "draw.h"

void	draw_entry(SDL_Renderer *renderer, int x, int y, char *str)
{
	// font rectangle
	draw_rectangle(renderer, x, y, 0x55, 0x55, 0x55, 0xff);

	TTF_Font	*Sans = TTF_OpenFont("Sans.ttf", 24);
	SDL_Color	White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface	*surfaceMessage = TTF_RenderText_Solid(Sans, str, White);
	SDL_Texture	*Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

}

void	draw_grill(SDL_Renderer *renderer, int grid_gap)
{
	// Draw grill in green
	SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0, 0x33);

	/*// Draw vertical lines*/
	for (int x = 0; x < WIN_WIDTH; x += grid_gap) {
		SDL_RenderDrawLine(renderer, x, 0, x, WIN_HEIGHT);
	}

	// Draw horizontal lines
	for (int y = 0; y < WIN_HEIGHT; y += grid_gap) {
		SDL_RenderDrawLine(renderer, 0, y, WIN_WIDTH, y);
	}
}

// x and y are coordinate in pixel, x_size and y_size are size in pixel
void	create_rectangle(SDL_Rect *rectangle, int x, int y, int width, int height)
{
	rectangle->x = x;
	rectangle->y = y;
	rectangle->w = width;
	rectangle->h = height;
}

void	draw_rectangle(SDL_Renderer *renderer, int x, int y, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	SDL_Rect	rectangle;

	// -1 and +1 to fit perfectly in square
	create_rectangle(&rectangle, x + 1, y + 1,
 			square_size - 1, square_size - 1);

	if (rectangle.y < NB_COLUMN * square_size && rectangle.x < NB_LINE * square_size) {
		SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
		SDL_RenderFillRect(renderer, &rectangle);
	}
}

