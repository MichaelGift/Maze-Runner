#include "../headers/main.h"

/**
 * changeColorIntensity - Changes the intensity of a color by multiplying
 * its RGB components by a factor.
 *
 * The function modifies the intensity of the given color by
 * scaling its RGB components.
 *
 * @color: Pointer to the color to be modified.
 * @factor: Factor by which to scale the RGB components of the color.
 *
 * Return: void
 */
void changeColorIntensity(color_t *color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * renderTerrain - Renders a textured terrain or wall column on the screen.
 *
 * The function calculates the texture coordinates based on the ray
 * intersection with the wall and draws texel colors on the screen
 * for a vertical column.
 *
 * @wallBottomPixel: Bottom pixel position of the wall/column on the screen.
 * @texelColor: Pointer to the texel color to be rendered.
 * @x: X-coordinate of the column on the screen.
 *
 * Return: void
 */
void renderTerrain(int wallBottomPixel, color_t *texelColor, int x)
{
	int y, texHeight, texWidth, texOffsetY, texOffsetX;
	float distance, ratio;

	texWidth = wallTextures[3].width;
	texHeight = wallTextures[3].height;
	for (y = wallBottomPixel - 1; y < SCREEN_HEIGTH; y++)
	{
		ratio = player.height / (y - SCREEN_HEIGTH / 2);
		distance = (ratio * PROJ_PLANE) /
			cos(rays[x].rayAngle - player.rotationAngle);
		texOffsetY = (int)abs((distance * sin(rays[x].rayAngle)) + player.y);
		texOffsetX = (int)abs((distance * cos(rays[x].rayAngle)) + player.x);
		texOffsetX = (int)(abs(texOffsetX * texWidth / 30) % texWidth);
		texOffsetY = (int)(abs(texOffsetY * texHeight / 30) % texHeight);
		*texelColor =
			wallTextures[4].texture_buffer[(texWidth * texOffsetY) + texOffsetX];
		drawPixel(x, y, *texelColor);
	}
}

/**
 * renderSkyBox - Renders a skybox or sky texture above a
 * wall/column on the screen.
 *
 * The function calculates the texture coordinates based on
 * the ray intersection with the sky and draws texel
 * colors on the screen for a vertical column.
 *
 * @wallTopPixel: Top pixel position of the wall/column on the screen.
 * @texelColor: Pointer to the texel color to be rendered.
 * @x: X-coordinate of the column on the screen.
 *
 * Return: void
 */
void renderSkyBox(int wallTopPixel, color_t *texelColor, int x)
{
	int y, texWidth, texHeight, texOffsetY, texOffsetX;

	texWidth = wallTextures[3].width;
	texHeight = wallTextures[3].height;
	for (y = 0; y < wallTopPixel; y++)
	{
		float distance, ratio;

		ratio = player.height / (y - SCREEN_HEIGTH / 2);
		distance = (ratio * PROJ_PLANE) /
			cos(rays[x].rayAngle - player.rotationAngle);
		texOffsetY = (int)abs((-distance * sin(rays[x].rayAngle)) + player.y);
		texOffsetX = (int)abs((-distance * cos(rays[x].rayAngle)) + player.x);
		texOffsetX = (int)(abs(texOffsetX * texWidth / 40) % texWidth);
		texOffsetY = (int)(abs(texOffsetY * texHeight / 40) % texHeight);
		*texelColor =
			wallTextures[6].texture_buffer[(texWidth * texOffsetY) + texOffsetX];
		drawPixel(x, y, *texelColor);
	}
}

/**
 * renderWorld - Renders the 3D world by casting rays
 * and rendering textured walls.
 *
 * The function calculates wall heights, determines textures,
 * and renders each vertical column of the screen with the
 * appropriate textures and colors.
 *
 * Return: void
 */
void renderWorld(void)
{
	int x, y, texNo, texWidth, texHeight, texOffsetX,
	    wallBottomPixel, wallStripHeight, wallTopPixel, distFromtop, texOffsetY;
	float perpDist, projectedWallHeight;
	color_t texelColor;

	for (x = 0; x < NUM_RAYS; x++)
	{
		perpDist = rays[x].distance * cos(rays[x].rayAngle - player.rotationAngle);
		projectedWallHeight = (TILE_SIZE / perpDist) * PROJ_PLANE;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (SCREEN_HEIGTH / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;
		wallBottomPixel = (SCREEN_HEIGTH / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > SCREEN_HEIGTH
			? SCREEN_HEIGTH : wallBottomPixel;
		texNo = rays[x].wallHitContent - 1;
		texWidth = wallTextures[texNo].width;
		texHeight = wallTextures[texNo].height;
		renderTerrain(wallBottomPixel, &texelColor, x);
		renderSkyBox(wallTopPixel, &texelColor, x);
		if (rays[x].wasHitVert)
			texOffsetX = (int)rays[x].wallHitY % TILE_SIZE;
		else
			texOffsetX = (int)rays[x].wallHitX % TILE_SIZE;
		for (y = wallTopPixel; y < wallBottomPixel; y++)
		{
			distFromtop = y + (wallStripHeight / 2) - (SCREEN_HEIGTH / 2);
			texOffsetY = distFromtop * ((float)texHeight / wallStripHeight);
			texelColor =
				wallTextures[texNo].texture_buffer[(texWidth * texOffsetY) + texOffsetX];
			if (rays[x].wasHitVert)
				changeColorIntensity(&texelColor, 0.5);
			drawPixel(x, y, texelColor);
		}
	}
}
