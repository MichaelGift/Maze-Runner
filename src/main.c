#include "../headers/main.h"

bool isGameRunning = false;
player_t player;
int tickSinceLastFrame;



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
 * renderStuff - Let there be light and there was light.
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
 * The start of the program
 * Create a game window, initializes game components
 * Creates while loop that tracks input,refreshes game state and renders the game world.
 * When the game window is destroyed the game ends.
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