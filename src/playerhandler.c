#include "../headers/main.h"

/**
 * updatePlayerPosition - Updates the player's position 
 * based on current movement and rotation parameters.
 * @param deltaTime: The time elapsed since the last frame update.
 * Return: void
 */
void updatePlayerPosition(float deltaTime)
{
    float moveStep, newXPos, newYPos;

    player.rotationAngle += player.turnDir * player.turnSpeed * deltaTime;
    moveStep = player.walkDir * player.walkSpeed * deltaTime;

    newXPos = player.x + cos(player.rotationAngle) * moveStep;
    newYPos = player.y + sin(player.rotationAngle) * moveStep;

    if (!isCollisionDetected(newXPos, newYPos))
    {
        player.x = newXPos;
        player.y = newYPos;
    }
}


/**
 * renderPlayerOnMinimap - Renders the player's position on the minimap.
 * The player is represented as a rectangle on the minimap, scaled by MINIMAP_SCALE_FACTOR.
 * Return: void
 */
void renderPlayerOnMinimap(void)
{
    drawRect(
        player.x * MINIMAP_SCALE_FACTOR,
        player.y * MINIMAP_SCALE_FACTOR,
        player.width * MINIMAP_SCALE_FACTOR,
        player.height * MINIMAP_SCALE_FACTOR,
        0xFFFFFFFF);
}