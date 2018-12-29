#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <switch.h>

int square_size = 5;

#define NB_COLUMN		WIN_HEIGHT / square_size
#define NB_LINE			WIN_WIDTH / square_size
#define CELL_ALIVE		true
#define CELL_DEAD		false
#define MIDDLE_Y		NB_COLUMN/2
#define MIDDLE_X		NB_LINE/2

#define CLEAR()			printf("\033[H\033[J")

#define CHECK_Y_MIN		(y - 1 > 0)
#define CHECK_Y_PLUS	(y + 1 < NB_COLUMN)
#define CHECK_X_MIN		(x - 1 > 0)
#define CHECK_X_PLUS	(x + 1 < NB_LINE)

#define WIN_WIDTH	1280
#define WIN_HEIGHT	720

#define SQUARE_SIZE 5

typedef struct		win_render
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}					win_render;


#endif
