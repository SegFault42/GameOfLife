#include "graphic.h"
#include "draw.h"
#include "nxui.h"

// Init Everything
NXUI_graphic	*NXUI_init(void)
{
	NXUI_graphic	*w_rend = NULL;

	romfsInit();
	// Init SDL2
	w_rend = (NXUI_graphic *)calloc(sizeof(NXUI_graphic), 1);
	if (w_rend == NULL)
		return (NULL);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error SDL_Init : %s", SDL_GetError());
		goto end;
	}

	if (TTF_Init() == -1) {
		fprintf(stderr, "Error TTF_Init : %s", TTF_GetError());
		goto end;
	}

	// Create window for Nintendo switch screen
	w_rend->window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	if (w_rend->window == NULL) {
		fprintf(stderr, "Error SDL_CreateWindow : %s", SDL_GetError());
		goto end;
	}

	// create Renderer
	w_rend->renderer = SDL_CreateRenderer(w_rend->window, -1, SDL_RENDERER_ACCELERATED);
	if (w_rend->renderer == NULL) {
		fprintf(stderr, "Error SDL_CreateRenderer : %s", SDL_GetError());
		goto end;
	}

	// Pick black color
	if (SDL_SetRenderDrawColor(w_rend->renderer, 0x00, 0x00, 0x00, 0x00)) {
		fprintf(stderr, "Error SDL_SetRenderDrawColor : %s", SDL_GetError());
		goto end;
	}

	// Clear screen in black
	if (SDL_RenderClear(w_rend->renderer) != 0) {
		fprintf(stderr, "Error SDL_RenderClear : %s", SDL_GetError());
		goto end;
	}

	// Init nlink debug
	#ifdef DEBUG
		socketInitializeDefault();
		nxlinkStdio();
	#endif

	return (w_rend);

	//De init everyting if something wrong
end:
	NXUI_de_init(w_rend);
	return (NULL);
}

// deinit and free memory
void	NXUI_de_init(NXUI_graphic *w_rend)
{
	SDL_DestroyRenderer(w_rend->renderer);
	SDL_DestroyWindow(w_rend->window);
	free(w_rend);
	SDL_Quit();
	TTF_Quit();
}

// Draw full rectangle
int	NXUI_draw_full_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height)
{
	SDL_Rect	rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = width;
	rectangle.h = height;

	return (SDL_RenderFillRect(renderer, &rectangle));
}

// Draw multiple full rectangle
int	NXUI_draw_full_rectangles(SDL_Renderer *renderer, const SDL_Rect *rectangle, int count)
{
	return (SDL_RenderFillRects(renderer, rectangle, count));
}

// Draw empty rectangle
int	NXUI_draw_empty_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height)
{
	SDL_Rect	rectangle;

	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = width;
	rectangle.h = height;

	return (SDL_RenderDrawRect(renderer, &rectangle));
}

// Draw multiple empty rectangle
int	NXUI_draw_empty_rectangles(SDL_Renderer *renderer, const SDL_Rect *rectangle, int count)
{
	return (SDL_RenderDrawRects(renderer, rectangle, count));
}

/*int	NXUI_draw_gradient_rectangle(SDL_Renderer *renderer, int x, int y, int width, int height, SDL_Color)*/
/*{*/
/*}*/

// Draw line
int	NXUI_draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
	return (SDL_RenderDrawLine(renderer, x1, y1, x2, y2));
}

// Draw multiples lines connected
int	NXUI_draw_lines(SDL_Renderer *renderer, const SDL_Point *points, int count)
{
	return (SDL_RenderDrawLines(renderer, points, count));
}

// Draw pixel
int	NXUI_draw_pixel(SDL_Renderer *renderer, int x, int y)
{
	return (SDL_RenderDrawPoint(renderer, x, y));
}

// Set drawing color
int	NXUI_set_color(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (SDL_SetRenderDrawColor(renderer, r, g, b, a));
}

int		NXUI_clear_screen(SDL_Renderer *renderer)
{
	return (SDL_RenderClear(renderer));
}

void	NXUI_draw_text(SDL_Renderer *renderer, NXUI_text text, uint8_t flag)
{
	TTF_Font	*font = NULL;
	SDL_Surface	*surface_message = NULL;
	SDL_Texture	*message = NULL;

	// Openfont with selected font and size
	font = TTF_OpenFont(text.font, text.font_size);
	if (font == NULL) {
		fprintf(stderr, "TTF_OpenFont: %s\n", TTF_GetError());
		return ;
	}

	// Render text
	if (flag & SOLID) {
		if (flag & TEXT) {
			surface_message = TTF_RenderText_Solid(font, text.text, text.color);
		} else if (flag & UTF8) {
			surface_message = TTF_RenderUTF8_Solid(font, text.text, text.color);
		} else if (flag & UNICODE) {
			surface_message = TTF_RenderUNICODE_Solid(font, text.text_unicode, text.color);
		/*} else if (flag & GLYPH) {*/
			/*surface_message = TTF_RenderGLYPH_Solid(font, text.text, text.color);*/
		}
	} else if (flag & SHADED) {
		if (flag & TEXT) {
			surface_message = TTF_RenderText_Shaded(font, text.text, text.color, text.color_background);
		} else if (flag & UTF8) {
			surface_message = TTF_RenderUTF8_Shaded(font, text.text, text.color, text.color_background);
		} else if (flag & UNICODE) {
			surface_message = TTF_RenderUNICODE_Shaded(font, text.text_unicode, text.color, text.color_background);
		/*} else if (flag & GLYPH) {*/
			/*surface_message = TTF_RenderGLYPH_Shaded(font, text.text, text.color, text.color_background);*/
		}
	} else if (flag & BLENDED) {
		if (flag & TEXT) {
			surface_message = TTF_RenderText_Blended(font, text.text, text.color);
		} else if (flag & UTF8) {
			surface_message = TTF_RenderUTF8_Blended(font, text.text, text.color);
		} else if (flag & UNICODE) {
			surface_message = TTF_RenderUNICODE_Blended(font, text.text_unicode, text.color);
		/*} else if (flag & GLYPH) {*/
			/*surface_message = TTF_RenderGLYPH_Blended(font, text.text, text.color);*/
		}
	}

	TTF_CloseFont(font);

	if (surface_message == NULL) {
		fprintf(stderr, "TTF_RenderText_Solid: %s\n", TTF_GetError());
		return ;
	}

	// Convert as texture
	message = SDL_CreateTextureFromSurface(renderer, surface_message);
	SDL_FreeSurface(surface_message);
	if (message == NULL) {
		fprintf(stderr, "SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
		return ;
	}

	// Set rectangle size
	text.rect.w = surface_message->w;
	text.rect.h = surface_message->h;

	SDL_RenderCopy(renderer, message, NULL, &text.rect);

	// free texture
	SDL_DestroyTexture(message);
}

void	NXUI_layout1(SDL_Renderer *renderer, char *title)
{
	// Init text struct
	NXUI_text	text = {
		.text = title,
		.color = {0xdd, 0xdd, 0xdd, 0xff},
		.color_background = {0x33, 0x33, 0x33, 0xff},
		.rect = {60, 30, 0, 0},
		.font = "romfs:/Fonts/NintendoStandard.ttf",
		.font_size = 42
	};

	// Clear screen
	NXUI_set_color(renderer, 0x33, 0x33, 0x33, 0xff); // Dark green
	NXUI_clear_screen(renderer);

	// Draw horizontal line
	NXUI_set_color(renderer, 0xaa, 0xaa, 0xaa, 0xff); // White
	NXUI_draw_line(renderer, 40, (WIN_HEIGHT/8), (WIN_WIDTH - 40), (WIN_HEIGHT/8));
	NXUI_draw_line(renderer, 40, (WIN_HEIGHT - WIN_HEIGHT/8), (WIN_WIDTH - 40), (WIN_HEIGHT - WIN_HEIGHT/8));

	// Draw vertical line
	NXUI_draw_line(renderer, (WIN_WIDTH/4), (WIN_HEIGHT/8) + 40, (WIN_WIDTH/4), (WIN_HEIGHT - WIN_HEIGHT/8) -40);

	// Draw Homebrew name
	NXUI_draw_text(renderer, text, UTF8 | SHADED);

	// Draw A and B button
	text.text = B_BUTTON " Back";
	text.rect.x = 1050;
	text.rect.y = 665;
	text.font_size = 20;
	NXUI_draw_text(renderer, text, UTF8 | SHADED);

	text.text = A_BUTTON " OK";
	text.rect.x = 1150;
	NXUI_draw_text(renderer, text, UTF8 | SHADED);
}

/*void	main_menu(win_render *w_rend)*/
/*{*/
	/*draw_entry(w_rend);*/
/*}*/

win_render	*graphic()
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

void	create_map(bool old_tab[][NB_LINE], win_render *w_rend)
{
	int	x = 0, y = 0;

	// Draw custom map
	while (true) {
		hidScanInput();

		u64 kHeld = hidKeysHeld(CONTROLLER_P1_AUTO);
		u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		// quit map editor
		if (kDown & KEY_B)
			break ;

		// Clear screen
		SDL_SetRenderDrawColor(w_rend->renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(w_rend->renderer);

		// Draw grill
		draw_grill(w_rend->renderer, square_size);

		//Capture input
		if (kHeld & KEY_RIGHT && x < NB_LINE) {
			x++;
		} else if (kHeld & KEY_LEFT && x > 0) {
			x--;
		} else if (kHeld & KEY_DOWN && y < NB_COLUMN) {
			y++;
		} else if (kHeld & KEY_UP && y > 0) {
			y--;
		} else if (kDown & KEY_A) {
			if (old_tab[y][x] == true)
				old_tab[y][x] = false;
			else
				old_tab[y][x] = true;
		} else if (kHeld & KEY_L && square_size > 5) {
			--square_size;
		} else if (kHeld & KEY_R && square_size < 100) {
			++square_size;
		}

		if (kHeld) {
			SDL_Delay(200);
		}

		// Draw cell on current postion
		if (old_tab[y][x] == CELL_ALIVE)
			draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0, 0xff, 0xff, 0xff);
		else
			draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0, 0xff, 0, 0xff);

		// Draw all cell
		for (int y = 0; y < NB_COLUMN; y++) {
			for (int x = 0; x < NB_LINE; x++) {
				if (old_tab[y][x] == CELL_ALIVE)
					draw_rectangle(w_rend->renderer, x * square_size, y * square_size, 0xff, 0xff, 0, 0xff);
			}
		}

		// Render to screen
		SDL_RenderPresent(w_rend->renderer);
		draw_entry(w_rend->renderer, 100, 100, "Hello");
	}
}
