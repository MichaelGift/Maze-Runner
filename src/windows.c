#include "../headers/main.h"

static SDL_Renderer *renderer;
static color_t *colorBuffer;
static SDL_Texture *colorBufferTexture;
static SDL_Window *window;

/**
 * createWindow - Initializes SDL, creates a window, renderer,
 * and initializes necessary buffers.
 *
 * The function initializes SDL, creates a borderless window that spans
 * the entire screen, creates a renderer for rendering graphics,
 * sets blend mode for transparency,
 * allocates memory for color buffer, and creates a texture for color
 * buffer rendering.
 *
 * Return: true if initialization succeeds, false otherwise.
 */
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

	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, screenW, screenH,
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

	colorBufferTexture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			SCREEN_WIDTH,
			SCREEN_HEIGTH);
	return (true);
}

/**
 * clearFrame - Clears the color buffer with the specified color.
 * The function fills the colorBuffer array with the given color.
 *
 * @color: The color to fill the buffer with.
 *
 * Return: void
 */
void clearFrame(color_t color)
{
	int i;

	for (i = 0; i < SCREEN_WIDTH * SCREEN_HEIGTH; i++)
		colorBuffer[i] = color;
}

/**
 * drawPixel - Draws a pixel at the specified coordinates in the color
 * buffer.
 *
 * The function sets the color of a single pixel in the colorBuffer array.
 *
 * @x: The x-coordinate of the pixel.
 * @y: The y-coordinate of the pixel.
 * @color: The color to set the pixel.
 *
 * Return: void
 */
void drawPixel(int x, int y, color_t color)
{
	colorBuffer[(SCREEN_WIDTH * y) + x] = color;
}

/**
 * redrawFrame - Redraws the frame by updating the texture and rendering to
 * the screen.
 *
 * The function updates the colorBufferTexture with the contents of
 * colorBuffer, renders it using the renderer, and presents it on the screen.
 *
 * Return: void
 */
void redrawFrame(void)
{
	SDL_UpdateTexture(colorBufferTexture, NULL, colorBuffer,
			(int)(SCREEN_WIDTH * sizeof(color_t)));

	SDL_RenderCopy(renderer, colorBufferTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/**
 * destroyWindow - Destroys SDL window, renderer, and frees allocated memory.
 * The function releases resources used by SDL, including colorBuffer
 * and colorBufferTexture,destroys the renderer and window,
 * and shuts down SDL subsystems.
 *
 * Return: void
 */
void destroyWindow(void)
{
	free(colorBuffer);
	SDL_DestroyTexture(colorBufferTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
