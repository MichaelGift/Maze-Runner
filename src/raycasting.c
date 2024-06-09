#include "../headers/main.h"

ray_t rays[NUM_RAYS];
static bool hasHitHorzWall, hasHitVertWall;
static float horzWallHitX, horzWallHitY, vertWallHitX, vertWallHitY;
static int horzWallContent, vertWallContent;

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

void vertIntersect(float angle)
{
    float vertTouchX, vertTouchY;
    float xIntercept, yIntercept, xStep, yStep;

    hasHitVertWall = false;
    vertWallHitX = 0;
    vertWallHitY = 0;
    vertWallContent = 0;

    xIntercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
    xIntercept += isRayFacingRight(angle) ? TILE_SIZE : 0;
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

void castRays(void)
{
    int ray;

    for (ray = 0; ray < NUM_RAYS; ray++)
    {
        float rayAngle = player.rotationAngle + atan((ray - NUM_RAYS / 2) / PROJ_PLANE);
        castRay(rayAngle, ray);
    }
}

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
