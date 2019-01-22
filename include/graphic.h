#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "common.h"

win_render	*graphic();
void	create_map(bool old_tab[][NB_LINE], win_render *w_rend);
//void	main_menu(win_render *w_rend);

#include "nxui.h"

#define WIN_WIDTH			1280
#define WIN_HEIGHT			720

#define A_BUTTON			"\ue0e0"
#define B_BUTTON			"\ue0e1"
#define X_BUTTON			"\ue0e2"
#define Y_BUTTON			"\ue0e3"
#define L_BUTTON			"\ue0e4"
#define R_BUTTON			"\ue0e5"
#define ZL_BUTTON			"\ue0e6"
#define ZR_BUTTON			"\ue0e7"
#define MULTI_ARROW_BUTTON	"\ue0ea"
#define ARROW_UP__BUTTON	"\ue0eb"
#define ARROW_DOWN_BUTTON	"\ue0ec"
#define ARROW_LEFT_BUTTON	"\ue0ed"
#define ARROW_RIGHT_BUTTON	"\ue0ee"
#define PLUS_BUTTON			"\ue0f1"
#define MINUS_BUTTON		"\ue0f2"
#define POWER_BUTTON		"\ue0f3"
#define HOME_BUTTON			"\ue0f4"
#define SHARE_BUTTON		"\ue0f5"

#define SOLID	1 << 0
#define SHADED	1 << 1
#define BLENDED	1 << 2

#define TEXT	1 << 3
#define UTF8	1 << 4
#define UNICODE	1 << 5
/*#define GLYPH	1 << 6*/

typedef struct			NXUI_graphic
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Surface			*window_surface;
}						NXUI_graphic;

typedef struct	NXUI_text
{
	char		*text;				// text to draw (TEXT and UTF8)
	Uint16		*text_unicode;		// text as unicode to draw (UNICODE)
	//Uint16		text_glyph;			// text as glyph to draw (GLYPH)

	SDL_Color	color;				// font color
	SDL_Color	color_background;	// background color (Only for shaded typo)

	SDL_Rect	rect;				// rect to position text

	char		*font;				// font name
	int			font_size;			// font size
	char		pad[4];				// padding
}				NXUI_text;

NXUI_graphic	*NXUI_init(void);
void			NXUI_de_init(NXUI_graphic *w_rend);

int				NXUI_draw_full_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height);
int				NXUI_draw_full_rectangles(SDL_Renderer *renderer, const SDL_Rect *rectangle, int count);

int				NXUI_draw_empty_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height);
int				NXUI_draw_empty_rectangles(SDL_Renderer *renderer, const SDL_Rect *rectangle, int count);

int				NXUI_draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
int				NXUI_draw_lines(SDL_Renderer *renderer, const SDL_Point *points, int count);

int				NXUI_set_color(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

int				NXUI_draw_pixel(SDL_Renderer *renderer, int x, int y);

int				NXUI_clear_screen(SDL_Renderer *renderer);

void			NXUI_draw_text(SDL_Renderer *renderer, NXUI_text text, uint8_t flag);

void			NXUI_layout1(SDL_Renderer *renderer, char *title);

#endif
