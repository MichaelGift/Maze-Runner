#include "../headers/main.h"

static const char *textureFiles[NUM_TEXTURES] = {
	"./assets/redbrick.png",
	"./assets/purplestone.png",
	"./assets/mossystone.png",
	"./assets/graystone.png",
	"./assets/colorstone.png",
	"./assets/bluestone.png",
	"./assets/wood.png",
	"./assets/eagle.png",
};

/**
 * loadTextures - Loads textures from files and stores them in the
 * wallTextures array.
 *
 * The function iterates through NUM_TEXTURES files, loads each
 * texture using libupng, and stores relevant information
 * such as texture dimensions and buffer in wallTextures array.
 *
 * Return: void
 */
void loadTextures(void)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
	{
		upng_t *upng;

		upng = upng_new_from_file(textureFiles[i]);
		if (upng != NULL)
		{
			upng_decode(upng);
			if (upng_get_error(upng) == UPNG_EOK)
			{
				wallTextures[i].upngTexture = upng;
				wallTextures[i].width = upng_get_width(upng);
				wallTextures[i].height = upng_get_height(upng);
				wallTextures[i].texture_buffer = (color_t *)upng_get_buffer(upng);
			}
		}
	}
}

/**
 * unloadTextures - Unloads textures stored in the wallTextures array
 * by freeing memory allocated for each texture.
 *
 * The function iterates through NUM_TEXTURES textures and frees
 * the upngTexture object associated with each.
 *
 * Return: void
 */
void unloadTextures(void)
{
	int i;

	for (i = 0; i < NUM_TEXTURES; i++)
		upng_free(wallTextures[i].upngTexture);
}
