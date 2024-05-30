#include "../headers/main.h"



/**
 * SDL_KEYDOWN_FUNC - process input when a key is down. ie pressed
 * 
 * @event: contains different event types
*/
void SDL_KEYDOWN_FUNC(SDL_Event event){
    /** Directional keys */
    if (event.key.keysym.sym == SDLK_ESCAPE)
        isGameRunning = false;
    if (event.key.keysym.sym == SDLK_UP)
        player.walkDir = +1;
    if (event.key.keysym.sym == SDLK_DOWN)
        player.walkDir = -1;
    if (event.key.keysym.sym == SDLK_RIGHT)
        player.turnDir =  +1;
    if (event.key.keysym.sym == SDLK_LEFT)
        player.turnDir = -1;

    /** Wasd Keys*/
    if (event.key.keysym.sym == SDLK_w)
		player.walkDir = +1;
	if (event.key.keysym.sym == SDLK_s)
		player.walkDir = -1;
	if (event.key.keysym.sym == SDLK_a)
		player.turnDir = -1;
	if (event.key.keysym.sym == SDLK_d)
		player.turnDir = +1;
}


/**
 * SDL_KEYUP_FUNC - process input when key is up. ie released
 * 
 * @event: contains different event types
*/
void SDL_KEYUP_FUNC(SDL_Event event){
    /** Directional keys */
    if (event.key.keysym.sym == SDLK_UP)
        player.walkDir = 0;
    if (event.key.keysym.sym == SDLK_DOWN)
        player.walkDir = 0;
    if (event.key.keysym.sym == SDLK_RIGHT)
        player.turnDir =  0;
    if (event.key.keysym.sym == SDLK_LEFT)
        player.turnDir = 0;

    /** Wasd Keys*/
    if (event.key.keysym.sym == SDLK_w)
		player.walkDir = 0;
	if (event.key.keysym.sym == SDLK_s)
		player.walkDir = 0;
	if (event.key.keysym.sym == SDLK_a)
		player.turnDir = 0;
	if (event.key.keysym.sym == SDLK_d)
		player.turnDir = 0;
}

/**
 * handleInput - process input from keyboard
*/
void handleInput(void) {
    SDL_Event event;

    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
        isGameRunning = false;
    else if (event.type == SDL_KEYDOWN)
        SDL_KEYDOWN_FUNC(event);
    else if (event.type == SDL_KEYUP)
        SDL_KEYUP_FUNC(event);
}