#ifndef MAIN_H

#include <SDL.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>


typedef uint32_t color_t;

/* Constants */
#define PI 3.14159265
#define SCREEN_WIDTH 720
#define SCREEN_HEIGTH 480

#define FPS 30
#define REFRESH_RATE (1000 / FPS )

/* Game State */
extern bool isGameRunning;


/* Player/Camera */
/**
 * struct player - struct for player
 * @x: x coordinate
 * @y: y coordinate
 * @width: player width
 * @height: player height
 * @turnDir: turn direction
 * @walkDir: walk direction
 * @rotationAngle: player/camera rotation angle
 * @walkSpeed: walk speed
 * @turnSpeed: Sensitivity when player looks around
*/
typedef struct player {
    float x;
    float y;
    float width;
    float height;
    int turnDir;
    int walkDir;
    float rotationAngle;
    float walkSpeed;
    float turnSpeed;
} player_t;

extern player_t player;
void updatePlayerPosition(float);

/* Main functions */
void startGame(void);


/* Window/Screen functions */
bool initializeWindow(void);

/* Input handling */
void handleInput(void);

#define MAIN_H
#endif
