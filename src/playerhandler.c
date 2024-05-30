#include "../headers/main.h"


/**
 * updatePlayerPosition - update player position based on inputs
 * @deltaTime: time since last frame
*/
void updatePlayerPosition(float deltaTime){
    float moveStep, newXPos, newYPos;

    player.rotationAngle += player.turnDir * player.turnSpeed * deltaTime;
    moveStep = player.walkDir * player.walkSpeed  * deltaTime;

    newXPos = player.x + cos(player.rotationAngle) * moveStep;
    newYPos = player.y + sin(player.rotationAngle) * moveStep;

    /**Handle colision*/
}