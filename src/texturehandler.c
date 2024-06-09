#include "../headers/main.h"

static const char* textureFiles[NUM_TEXTURES] = {
    "./assets/redbrick.png",
    "./assets/purplestone.png",
    "./assets/mossystone.png",
    "./assets/graystone.png",
    "./assets/colorstone.png",
    "./assets/bluestone.png",
    "./assets/wood.png",
    "./assets/nightsky.png"
};

/**
 * loadWallTextures - loads textures into positions
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

void unloadTextures(void)
{
    int i;

	for (i = 0; i < NUM_TEXTURES; i++)
		upng_free(wallTextures[i].upngTexture);
}