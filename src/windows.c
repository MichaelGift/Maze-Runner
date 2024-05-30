#include "../headers/main.h"

static SDL_Renderer *renderer;
static color_t *colorBuffer;
static SDL_Texture *colorBufferTexture;
static SDL_Window *window;

bool createWindow(void)
{

	SDL_DisplayMode displayMode;
	int screenW, screenH;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
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
		SDL_WINDOW_BORDERLESS);

	if (!window)
	{
		fprintf(stderr, "Error creating sdl window.\n");
		return (false);
	}

	renderer = SDL_CreateRenderer(window, -1, 1);
	if (!renderer)
	{
		fprintf(stderr, "Error creating SDL renderer. \n");
		return (false);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	colorBuffer = malloc(sizeof(color_t) * SCREEN_WIDTH * SCREEN_HEIGTH);

	colorBufferTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGTH);
	return (true);
}

void clearFrame(color_t color)
{
	int i;

	for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGTH; i++)
		colorBuffer[i] = color;
}

void drawPixel(int x, int y, color_t color)
{
	colorBuffer[(SCREEN_WIDTH * y) + x] = color
}

void redrawFrame(void)
{
	SDL_UpdateTexture(
		colorBufferTexture,
		NULL,
		colorBuffer,
		(int)(SCREEN_WIDTH * sizeof(color_t)));
	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void destroyWindow()
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}