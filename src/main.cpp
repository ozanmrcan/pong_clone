#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>

#include "RenderWindow.h"
#include "Entity.h"
#include "Player.h"
#include "Ball.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int BASE_PLAYER_VELOCITY = 6;

//these can be randomized at the start
const double BASE_BALL_VELX = 4;
const double BASE_BALL_VELY = 2;
const int WIN_CONDITION = 10;

enum left_right
{
	RIGHT = 1,
	LEFT = -1
};

int main(int argc, char* args[])
{	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	std::cout << "SDL_Init failed, SDL_Error: " << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_PNG))
	std::cout << "IMG_Init failed, SDL_Error: " << SDL_GetError() << std::endl;

	if (TTF_Init() == -1)
		std::cout << "TTF_Init failed, SDL_Error: " << SDL_GetError() << std::endl;

	RenderWindow window{ "Pong Clone", SCREEN_WIDTH, SCREEN_HEIGHT };

	// font for all text
	TTF_Font* font = TTF_OpenFont("assets/fonts/ARCADE_I.ttf", 28);
	if (font == NULL)
		std::cout << "TTF_OpenFont failed, SDL_Error: " << SDL_GetError() << std::endl;

	// midline
	SDL_Texture* midlineTexture = window.loadTexture("assets/images/midline.png");
	Entity midline{ SCREEN_WIDTH / 2 - 3, 0, midlineTexture };
	Entity leftline{ 47, 0, midlineTexture };
	Entity rightline{ SCREEN_WIDTH - 42, 0, midlineTexture };
	// ball
	SDL_Texture* ballTexture = window.loadTexture("assets/images/ball.png");
	Ball ball{(SCREEN_WIDTH / 2 - 16), (SCREEN_HEIGHT / 2 - 16), ballTexture, BASE_BALL_VELX, BASE_BALL_VELY}; // get rid of hard codeds
	// right player
	SDL_Texture* rPlayerTexture = window.loadTexture("assets/images/rect.png");
	Player rPlayer{SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2 - 96 , rPlayerTexture};
	// left player
	SDL_Texture* lPlayerTexture = window.loadTexture("assets/images/rect.png");
	Player lPlayer{ 38, SCREEN_HEIGHT / 2 - 96 , lPlayerTexture };


	Uint64 currentTick = SDL_GetPerformanceCounter();	
	Uint64 lastTick = 0;
	double deltaTime = 0;

	SDL_Event event;

	std::string winnerText;
	bool gameRunning = true;
	while (gameRunning)
	{

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameRunning = false;
			}
		}

		if (rPlayer.getScore() == WIN_CONDITION) {
			gameRunning = false;
			winnerText = "Right Player Won!";
			break;
		}

		if (lPlayer.getScore() == WIN_CONDITION) {
			gameRunning = false;
			winnerText = "Left Player Won!";
			break;
		}

		// hmmmmmmmmmmmmmmmmmmmm
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)( (currentTick - lastTick) * 1000 / (double)SDL_GetPerformanceFrequency() );

		// Player movement 
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		if (currentKeyStates[SDL_SCANCODE_UP])
		{
			rPlayer.move(BASE_PLAYER_VELOCITY, deltaTime, SCREEN_HEIGHT);
		}
		if (currentKeyStates[SDL_SCANCODE_DOWN])
		{
			rPlayer.move(-BASE_PLAYER_VELOCITY, deltaTime, SCREEN_HEIGHT);
		}
		if (currentKeyStates[SDL_SCANCODE_W])
		{
			lPlayer.move(BASE_PLAYER_VELOCITY, deltaTime, SCREEN_HEIGHT);
		}
		if (currentKeyStates[SDL_SCANCODE_S])
		{
			lPlayer.move(-BASE_PLAYER_VELOCITY, deltaTime, SCREEN_HEIGHT);
		}
		int direction = ball.move(deltaTime, rPlayer, lPlayer, SCREEN_HEIGHT, SCREEN_WIDTH);
		// ball movement, if a player scores
		if (direction == RIGHT) // if right scores
		{
			ball.resetPosition(SCREEN_HEIGHT, SCREEN_WIDTH);
			ball.setRandomVelocity(LEFT, BASE_BALL_VELX);
		}
		if (direction == LEFT) // if left scores
		{
			ball.resetPosition(SCREEN_HEIGHT, SCREEN_WIDTH);
			ball.setRandomVelocity(RIGHT, BASE_BALL_VELX);
		}

		window.renderingCycle(midline, leftline, rightline, ball, rPlayer, lPlayer, font, SCREEN_WIDTH);
	}
	
	bool endScreen = true;
	while (endScreen)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				endScreen = false;
			}
		}

		window.clear();
		window.renderText(font, winnerText, SCREEN_WIDTH/2, 300, 1000, 200);
		window.display();
	}

	window.cleanUp();
	SDL_Quit();
	IMG_Quit();

	return 0;
}