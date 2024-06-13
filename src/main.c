#include "../headers/main.h"

bool isGameRunning = false;
player_t player;
int tickSinceLastFrame;


/**
 * startGame - Initializes the game by setting up the player properties 
 * and loading textures.
 * Return: void
 */
void startGame(void){
	player.x = SCREEN_WIDTH / 2;
	player.y = SCREEN_HEIGTH / 2;
	player.width = 1;
	player.height = 25;
	player.walkDir = 0;
	player.walkSpeed = 100;
	player.turnDir = 0;
	player.turnSpeed = 45 * (PI / 180);
	player.rotationAngle = PI / 2;
	loadTextures();
}

/**
 * updateGameState - Updates the game state by controlling the frame rate 
 * and updating player position and ray casting.
 * Return: void
 */
void updateGameState(void){
	float DeltaTime;
	int timeToWait = REFRESH_RATE - (SDL_GetTicks() - tickSinceLastFrame);

	if (timeToWait > 0 && timeToWait <= REFRESH_RATE){
		SDL_Delay(timeToWait);
	}

	DeltaTime = (SDL_GetTicks() - tickSinceLastFrame) / 1000.0f;

	tickSinceLastFrame = SDL_GetTicks();

	updatePlayerPosition(DeltaTime);
	castRays();
}

/**
 * renderStuff - Renders all the necessary elements on the screen, 
 * including the world, minimap, and player.
 * Return: void
 */
void renderStuff(){
	clearFrame(0xFF000000);

	renderWorld();

	renderMinimap();
	renderPlayerFOV();
	renderPlayerOnMinimap();

	redrawFrame();
}

void endGame(void)
{
	unloadTextures();
	destroyWindow();
}


/**
 * main - The entry point of the game application. 
 * Initializes the game, handles the game loop, and cleans up resources.
 * return: int - Returns 0 upon successful completion.
 */
int main(void) {
	isGameRunning = createWindow();

	startGame();
	while (isGameRunning)
	{
		handleInput();
		updateGameState();
		renderStuff();
	}
	/**Becuase why not*/
	endGame();
	return (0);
}