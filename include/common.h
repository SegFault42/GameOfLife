#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define NB_COLUMN		50
#define NB_LINE			50
#define CELL_ALIVE		'o'
#define CELL_DEAD		'.'
#define MIDDLE_Y		NB_COLUMN/2
#define MIDDLE_X		NB_LINE/2

#define CLEAR()			printf("\033[H\033[J")

#define CHECK_Y_MIN		(y - 1 > 0)
#define CHECK_Y_PLUS	(y + 1 < NB_COLUMN)
#define CHECK_X_MIN		(x - 1 > 0)
#define CHECK_X_PLUS	(x + 1 < NB_LINE)

#endif
