#include "../headers/main.h"

/**
 * drawRect - Draws a rectangle on the screen with the specified dimensions
 * and color.
 * @x: The x-coordinate of the top-left corner of the rectangle.
 * @y: The y-coordinate of the top-left corner of the rectangle.
 * @width: The width of the rectangle.
 * @height: The height of the rectangle.
 * @color: The color of the rectangle.
 * Return: void
 */
void drawRect(int x, int y, int width, int height, color_t color)
{
	int i, j;

	for (i = x; i <= (x + width); i++)
		for (j = y; j <= (y + height); j++)
			drawPixel(i, j, color);
}


/**
 * drawLine - Draws a line on the screen between two points with the
 * specified color.
 * @x0: The x-coordinate of the starting point of the line.
 * @y0: The y-coordinate of the starting point of the line.
 * @x1: The x-coordinate of the ending point of the line.
 * @y1: The y-coordinate of the ending point of the line.
 * @color: The color of the line.
 * Return: void
 */
void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	float xIncrement, yIncrement, currentX, currentY;
	int i, longestSideLength, deltaX,  deltaY;

	deltaX = (x1 - x0);
	deltaY = (y1 - y0);

	longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

	xIncrement = deltaX / (float)longestSideLength;
	yIncrement = deltaY / (float)longestSideLength;

	currentX = x0;
	currentY = y0;

	for (i = 0; i < longestSideLength; i++)
	{
		drawPixel(round(currentX), round(currentY), color);
		currentX += xIncrement;
		currentY += yIncrement;
	}
}
