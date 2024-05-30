#include "../headers/main.h"

bool isGameRunning = false;
player_t player;
int tickSinceLastFrame;

int main(void) {
	isGameRunning = initializeWindow();

	startGame();
	while (isGameRunning)
	{
		handleInput();
		updateGameState();
		/* 
		RenderGraphics(); 
		*/
	}
	destroyGame();
	return (0);
}

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

	/**PaintWalls()*/
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

	/**castAllRays()*/
}