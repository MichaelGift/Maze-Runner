#include "../headers/main.h"


/**
 * isRayFacingUp - Determines if a ray at the given angle is facing upwards
 *
 * @angle: The angle of the ray in radians.
 *
 * Return: true if the ray is facing upwards, false otherwise.
 */
bool isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

/**
 * isRayFacingDown - Determines if a ray at the given angle is facing
 * downwards.
 *
 * @angle: The angle of the ray in radians.
 *
 * Return: true if the ray is facing downwards, false otherwise.
 */
bool isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

/**
 * isRayFacingRight - Determines if a ray at the given angle is facing
 * rightwards.
 *
 * @angle: The angle of the ray in radians.
 *
 * Return: true if the ray is facing rightwards, false otherwise.
 */
bool isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * isRayFacingLeft - Determines if a ray at the given angle is facing
 * leftwards.
 *
 * @angle: The angle of the ray in radians.
 *
 * Return: true if the ray is facing leftwards, false otherwise.
 */
bool isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}

/**
 * calculateDistance - Calculates the Euclidean distance between
 * two points (x1, y1) and (x2, y2).
 *
 * @x1: Same as y1.
 * @y1: Coordinates of the first point.
 * @x2: Same as y2.
 * @y2: Coordinates of the second point.
 *
 * Return: The distance between the two points.
 */
float calculateDistance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}
