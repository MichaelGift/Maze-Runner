#include "Header.h"


static SDL_Renderer *renderer;
static color_t *colorBuffer;
static SDL_Window *window;



bool initializeWindow(void) {

	SDL_DisplayMode displayMode;
	int screenW, screenH;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return (true);
	}

	SDL_GetCurrentDisplayMode(0, &displayMode);
	screenW = displayMode.w;
	screenH = displayMode.h;
	window = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenW,
		screenH,
		SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Error creating sdl window.\n");
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, 1);
	if (!renderer) {
		fprintf(stderr, "Error creating SDL renderer. \n");
		return (false);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);


	return (true);
}