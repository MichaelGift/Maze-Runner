#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <cfloat>
#include "upng.h"

typedef uint32_t color_t;

/* Constants */
#define TILE_SIZE 64
#define PI 3.14159265
#define PIx2 6.28318530
#define SCREEN_WIDTH (MAP_COLS * TILE_SIZE)
#define SCREEN_HEIGTH (MAP_ROWS * TILE_SIZE)
#define NUM_TEXTURES 8

#define MINIMAP_SCALE_FACTOR 0.2
#define NUM_RAYS SCREEN_WIDTH

#define FOV_ANGLE (60 * (PI / 180))
#define PROJ_PLANE ((SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2))

#define FPS 30
#define REFRESH_RATE (1000 / FPS)

#define MAP_ROWS 13
#define MAP_COLS 20

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
typedef struct player
{
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
void renderPlayerOnMinimap(void);

/* Main functions */
void startGame(void);
void renderStuff(void);


/* Window/Screen functions */
bool createWindow(void);
void clearFrame(color_t);
void drawPixel(int, int, color_t);
void redrawFrame(void);
void destroyWindow(void);

/* Input handling */
void handleInput(void);

/* Texture handler */
/**
 * struct texture - struct for textures
 * @width: texture width
 * @height: texture height
 * @texture_buffer: pointer to texture buffer
 * @upngTexture: pointer to upng buffer
*/
typedef struct texture
{
	int width;
	int height;
	color_t *texture_buffer;
	upng_t *upngTexture;
} texture_t;

texture_t wallTextures[NUM_TEXTURES];

void loadTextures(void);
void unloadTextures(void);


/* Ray casting*/
/**
 * struct ray - struct for the textures
 * @rayAngle: ray angle
 * @wallHitX: wall hit x coordinate
 * @wallHitY: wall hit x coordinate
 * @distance: ditance to the wall
 * @wasHitVert: verify hit vertical
 * @wallHitContent: wall hit content
 */

typedef struct ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	bool wasHitVert;
	int wallHitContent;
} ray_t;

extern ray_t rays[NUM_RAYS];

void castRays(void);
void castRay(float, int);
void horzIntersect(float);
void vertIntersect(float);
float calculateDistance(float, float, float, float);
void renderPlayerFOV(void);


bool isRayFacingDown(float);
bool isRayFacingUp(float);
bool isRayFacingLeft(float);
bool isRayFacingRight(float);


/*Map handler*/
bool isInsideMap(float, float);
bool isCollisionDetected(float, float);
int getMapValue(int, int);
void renderMinimap(void);


/**Wall Env handler*/
void renderWorld(void);
void renderTerrain(int, color_t, int);
void renderSkyBox(int, color_t, int);
void changeColorIntensity(color_t, float);

/*Draw*/
void drawRect(int, int, int, int, color_t);
void drawLine(int, int, int, int, color_t);

#endif
