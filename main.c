#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#define NB_COLUMN		20
#define NB_LINE			20
#define CELL_ALIVE		'o'
#define CELL_DEAD		'.'

#define clear()			printf("\033[H\033[J")
#define CHECK_Y_MIN		(y - 1 > 0)
#define CHECK_Y_PLUS	(y + 1 < NB_COLUMN)
#define CHECK_X_MIN		(x - 1 > 0)
#define CHECK_X_PLUS	(x + 1 < NB_LINE)

uint8_t	rule(char tab[][NB_LINE], const int x, const int y)
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

bool	dead_or_alive(char tab[][NB_LINE], const int x, const int y)
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

#define MIDDLE_Y NB_COLUMN/2
#define MIDDLE_X NB_LINE/2

int	main()
{
	char	old_tab[NB_COLUMN][NB_LINE];
	char	new_tab[NB_COLUMN][NB_LINE];

	memset(old_tab, CELL_DEAD, sizeof(old_tab));

	old_tab[MIDDLE_Y][MIDDLE_X] = CELL_ALIVE;
	old_tab[MIDDLE_Y][MIDDLE_X + 1] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 1][MIDDLE_X - 1] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 1][MIDDLE_X] = CELL_ALIVE;
	old_tab[MIDDLE_Y + 2][MIDDLE_X] = CELL_ALIVE;

	old_tab[3][3] = CELL_ALIVE;
	old_tab[3][4] = CELL_ALIVE;
	old_tab[3][5] = CELL_ALIVE;

	memcpy(new_tab, old_tab, sizeof(new_tab));

	while (0x1) {
		clear();
		printf("\x1b[0;0H");
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				printf("%c", new_tab[y][x]);
			}
			printf("\n");
		}
	
	
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (dead_or_alive(old_tab, x, y) == true)
					new_tab[y][x] = CELL_ALIVE;
				else
					new_tab[y][x] = CELL_DEAD;
			}
		}
		memcpy(old_tab, new_tab, sizeof(old_tab));
		usleep(50000);
		printf("\n");
	}
}
