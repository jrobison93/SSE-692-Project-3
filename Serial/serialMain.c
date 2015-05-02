#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>

struct Ball
{
	int x, y, width, height, dx, dy;
};

struct Paddle
{
	int x, y, width, height, score;
};


struct Ball ball;
struct Paddle player;
struct Paddle ai;

int WIDTH = 100;
int HEIGHT = 30;
int ch;
WINDOW* local_window;

int gameOver;


#include "serialPhysics.c"
#include "serialGraphics.c"
#include "serialUserInput.c"
#include "serialGameLogic.c"

int main(int argc, char* argv[])
{
	clock_t t;
	float timeDiff;
	int i;

	initializeGame();
	local_window = initializeBoard ();


	while(gameOver == 0)
	{
		// Get the start time
		t = clock();


		// Start the threads
		inputCapture();
		checkCollisions();
		updateGame();
		screenDraw();



		// Calculate how long the iteration took to run
		t = clock() - t;
		timeDiff = (((float) t) / CLOCKS_PER_SEC) * 1000;


		// If the alloted time for the execution is not over, sleep
		if(timeDiff < (1000 / 30))
		{
			usleep(((1000 / 30) - timeDiff) * 1000);
		}

	}


	return 0;
}


