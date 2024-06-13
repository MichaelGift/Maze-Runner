#include "../headers/main.h"

static const int map[MAP_ROWS][MAP_COLS] = {
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
{3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3},
{3, 0, 4, 0, 0, 0, 4, 4, 4, 4, 0, 3, 0, 0, 4, 4, 0, 3, 3, 3},
{3, 0, 4, 0, 3, 0, 4, 0, 0, 4, 0, 0, 0, 4, 4, 0, 0, 0, 0, 3},
{3, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 4, 0, 3},
{3, 0, 0, 0, 3, 4, 4, 4, 4, 4, 4, 0, 4, 4, 0, 4, 0, 4, 0, 3},
{3, 3, 3, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 4, 4, 4, 0, 3},
{3, 3, 3, 0, 3, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 4, 0, 0, 0, 3},
{3, 0, 0, 0, 3, 0, 4, 0, 0, 0, 0, 0, 4, 0, 0, 4, 0, 4, 0, 3},
{3, 3, 0, 3, 3, 0, 4, 0, 3, 3, 0, 0, 4, 0, 0, 4, 0, 4, 0, 3},
{3, 0, 0, 3, 3, 0, 4, 0, 0, 3, 0, 0, 0, 0, 0, 4, 0, 0, 0, 3},
{3, 0, 0, 0, 3, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3},
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0} };

/**
 * getMapValue - Retrieves the value from the map
 * at the specified row and column.
 *
 * @row: The row index of the map.
 * @col: The column index of the map.
 *
 * Return: int - The value at the specified position in the map.
 */
int getMapValue(int row, int col)
{
	return (map[row][col]);
}

/**
 * renderMinimap - Renders a minimap of the game world based on the map array.
 *
 * The minimap displays each tile as a rectangle colored
 * based on its value in the map array.
 *
 * Return: void
 */
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

/**
 * isCollisionDetected - Checks if a collision is detected at the
 * specified coordinates (x, y) in the game world.
 *
 * The function determines if the coordinates are out of bounds
 * or if they correspond to a non-walkable area on the map.
 *
 * @x: The x-coordinate to check for collision.
 * @y: The y-coordinate to check for collision.
 *
 * Return: bool - Returns true if a collision is detected, otherwise false.
 */
bool isCollisionDetected(float x, float y)
{
	int mapXGrid, mapYGrid;

	if (x < 0 || x >= MAP_COLS * TILE_SIZE ||
		y < 0 || y >= MAP_ROWS * TILE_SIZE)
		return (true);

	mapXGrid = floor(x / TILE_SIZE);
	mapYGrid = floor(y / TILE_SIZE);

	return (map[mapYGrid][mapXGrid] != 0);
}

/**
 * isInsideMap - Checks if the given coordinates (x, y)
 * are inside the boundaries of the game map.
 *
 * @x: The x-coordinate to check.
 * @y: The y-coordinate to check.
 *
 * Return: bool - Returns true if (x, y)
 * are inside the map boundaries, else false.
 */
bool isInsideMap(float x, float y)
{
	return (x >= 0 && x <= MAP_COLS * TILE_SIZE &&
			y >= 0 && y <= MAP_ROWS * TILE_SIZE);
}
