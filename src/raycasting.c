#include "../headers/main.h"

ray_t rays[NUM_RAYS];
static bool hasHitHorzWall, hasHitVertWall;
static float horzWallHitX, horzWallHitY, vertWallHitX, vertWallHitY;
static int horzWallContent, vertWallContent;
/**
 * horzIntersect - Performs horizontal ray casting and determines 
 * if the ray intersects with a horizontal wall.
 * @param angle: The angle of the ray relative to the player's view.
 * Return: void
 */
void horzIntersect(float angle)
{
    float horzTouchX, horzTouchY, xIntercept, yIntercept, xStep, yStep;

    hasHitHorzWall = false;
    horzWallHitX = horzWallHitY = horzWallContent = 0;

    yIntercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
    yIntercept += isRayFacingDown(angle) ? TILE_SIZE : 0;

    xIntercept = player.x + (yIntercept - player.y) / tan(angle);

    yStep = TILE_SIZE;
    yStep *= isRayFacingUp(angle) ? -1 : 1;
    xStep = TILE_SIZE / tan(angle);
    xStep *= (isRayFacingLeft(angle) && xStep > 0) ? -1 : 1;
    xStep *= (isRayFacingRight(angle) && xStep < 0) ? -1 : 1;
    horzTouchX = xIntercept;
    horzTouchY = yIntercept;

    while (isInsideMap(horzTouchX, horzTouchY))
    {
        float xToCheck = horzTouchX;
        float yToCheck = horzTouchY + (isRayFacingUp(angle) ? -1 : 0);

        if (isCollisionDetected(xToCheck, yToCheck))
        {
            horzWallHitX = horzTouchX;
            horzWallHitY = horzTouchY;

            horzWallContent = getMapValue((int)floor(yToCheck / TILE_SIZE),
                                          (int)floor(xToCheck / TILE_SIZE));

            hasHitHorzWall = true;
            break;
        }
        horzTouchX += xStep;
        horzTouchY += yStep;
    }
}

/**
 * vertIntersect - Performs vertical ray casting and determines if the ray intersects with a vertical wall.
 * @param angle: The angle of the ray relative to the player's view.
 * Return: void
 */
void vertIntersect(float angle)
{
    float vertTouchX, vertTouchY;
    float xIntercept, yIntercept, xStep, yStep;

    hasHitVertWall = false;
    vertWallHitX = 0;
    vertWallHitY = 0;
    vertWallContent = 0;

    xIntercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    yIntercept = isRayFacingRight(angle) ? TILE_SIZE : 0;
    yIntercept = player.y + (xIntercept - player.x) * tan(angle);

    xStep = TILE_SIZE;
    xStep *= isRayFacingLeft(angle) ? -1 : 1;
    yStep = TILE_SIZE * tan(angle);
    yStep *= (isRayFacingUp(angle) && yStep > 0) ? -1 : 1;
    yStep *= (isRayFacingDown(angle) && yStep < 0) ? -1 : 1;
    vertTouchX = xIntercept;
    vertTouchY = yIntercept;

    while (isInsideMap(vertTouchX, vertTouchY))
    {
        float xToCheck = vertTouchX + (isRayFacingLeft(angle) ? -1 : 0);
        float yToCheck = vertTouchY;

        if (isCollisionDetected(xToCheck, yToCheck))
        {
            vertWallHitX = vertTouchX;
            vertWallHitY = vertTouchY;
            vertWallContent = getMapValue((int)floor(yToCheck / TILE_SIZE),
                                          (int)floor(xToCheck / TILE_SIZE));

            hasHitVertWall = true;
            break;
        }
        vertTouchX += xStep;
        vertTouchY += yStep;
    }
}


/**
 * castRay - Casts a ray at a specified angle and determines the distance to the nearest wall hit (horizontal or vertical).
 * @param angle: The angle of the ray relative to the player's view.
 * @param id: The identifier of the ray being cast.
 * Return: void
 */
void castRay(float angle, int id)
{
    float horzHitDist, vertHitDist;

    angle = remainder(angle, PIx2);
    if (angle < 0)
        angle = PIx2 + angle;

    horzIntersect(angle);
    vertIntersect(angle);

    horzHitDist = hasHitHorzWall
                      ? calculateDistance(player.x, player.y, horzWallHitX, horzWallHitY)
                      : FLT_MAX;
    vertHitDist = hasHitVertWall
                      ? calculateDistance(player.x, player.y, vertWallHitX, vertWallHitY)
                      : FLT_MAX;

    if (vertHitDist < horzHitDist)
    {
        rays[id].distance = vertHitDist;
        rays[id].wallHitX = vertWallHitX;
        rays[id].wallHitY = vertWallHitY;
        rays[id].wallHitContent = vertWallContent;
        rays[id].wasHitVert = true;
        rays[id].rayAngle = angle;
    }
    else
    {
        rays[id].distance = horzHitDist;
        rays[id].wallHitX = horzWallHitX;
        rays[id].wallHitY = horzWallHitY;
        rays[id].wallHitContent = horzWallContent;
        rays[id].wasHitVert = false;
        rays[id].rayAngle = angle;
    }
}


/**
 * castRays - Casts rays from the player's viewpoint across the projection plane.
 * Each ray is cast at a specific angle relative to the player's rotation angle.
 * The function iterates over all rays and calculates their angles before calling castRay.
 * Return: void
 */
void castRays(void)
{
    int ray;

    for (ray = 0; ray < NUM_RAYS; ray++)
    {
        float rayAngle = player.rotationAngle + atan((ray - NUM_RAYS / 2) / PROJ_PLANE);
        castRay(rayAngle, ray);
    }
}


/**
 * renderPlayerFOV - Renders the player's field of view (FOV) 
 * by drawing lines from the player's position to each ray's wall h
 * it position.
 * 
 * The function iterates over rays with a step of 50 to draw lines 
 * representing the player's FOV on the minimap.
 * return: void
 */
void renderPlayerFOV(void)
{
    int i;

	for (i = 0; i < NUM_RAYS; i += 50)
	{
		drawLine(
			player.x * MINIMAP_SCALE_FACTOR,
			player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
	}
}
