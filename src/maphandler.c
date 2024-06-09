#include "../headers/main.h"

static const int map[MAP_ROWS][MAP_COLS] = {
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}
{6, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 6}
{6, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 6, 0, 0, 1, 6, 0, 1, 1, 6}
{6, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 6, 0, 7, 7, 0, 0, 0, 1, 6}
{6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 6, 1, 0, 0, 0, 0, 7, 1, 6}
{6, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 7, 1, 6}
{6, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 7, 7, 1, 6}
{6, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 6}
{6, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 7, 0, 0, 1, 0, 1, 0, 6}
{6, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 7, 0, 0, 1, 0, 1, 1, 6}
{6, 0, 0, 6, 6, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 6}
{6, 0, 0, 0, 6, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 6}
{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6} };

int getMapValue(int row, int col)
{
	return (map[row][col]);
}

void renderMinimap(void)
{
	int i, j, tileX, tileY;
	color_t tileColor;

	for (i = 0; i < MAP_ROWS; i++)
	{
		for (j = 0; j < MAP_COLS; j++)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			tileColor = map[i][j] != 0 ? 0xFFFFFFFF : 0x00000000;

			drawRect(
				tileX * MINIMAP_SCALE_FACTOR,
				tileY * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				tileColor
			);
		}
	}
}

bool isCollisionDetected(float x, float y)
{
	int mapXGrid, mapYGrid;

	if (x < 0 || x >= MAP_COLS * TILE_SIZE ||
		y < 0 || y >= MAP_ROWS * TILE_SIZE)
		return true;

	mapXGrid = floor(x / TILE_SIZE);
	mapYGrid = floor(y / TILE_SIZE);

	return (map[mapYGrid][mapXGrid] != 0);
}

bool isInsideMap(float x, float y)
{
	return (x >= 0 && x <= MAP_COLS * TILE_SIZE &&
			y >= 0 && y <= MAP_ROWS * TILE_SIZE);
}