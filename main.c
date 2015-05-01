#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
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

int gameOver;

pthread_rwlock_t ballLock;
pthread_rwlock_t playerLock;
pthread_rwlock_t aiLock;


#include "physics.c"
#include "graphics.c"
#include "userInput.c"
#include "gameLogic.c"

int main(int argc, char* argv[])
{
	pthread_t* thread_handles;
	
	thread_handles = malloc(4 * sizeof(pthread_t));

	pthread_rwlock_init(&ballLock, NULL);
	pthread_rwlock_init(&playerLock, NULL);
	pthread_rwlock_init(&aiLock, NULL);


	clock_t t;
	float timeDiff;
	int i;

	initializeGame();


	while(gameOver == 0)
	{
		// Get the start time
		t = clock();


		// Start the threads
		pthread_create(&thread_handles[0], NULL, /* User Input Function */, NULL);
		pthread_create(&thread_handles[1], NULL, /* Physics Function */, NULL);
		pthread_create(&thread_handles[2], NULL, /* Game Logic Function */, NULL);
		pthread_create(&thread_handles[3], NULL, /* Graphics Funciton */, NULL);


		
		// Wait for threads to end
		for(i = 0; i < 4; i++)
		{
			pthread_join(thread_handles[i], NULL);
		}


		// Calculate how long the iteration took to run
		t = clock() - t;
		timeDiff = (((float) t) / CLOCKS_PER_SEC) * 1000;


		// If the alloted time for the execution is not over, sleep
		if(timeDiff < (1000 / 30))
		{
			usleep(((1000 / 30) - timeDiff) * 1000);
		}

	}

	free(thread_handles);
	return 0;
}


