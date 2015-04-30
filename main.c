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
	int x, y, width, height;
};

int gameOver;

int main(int argc, char* argv[])
{
	pthread_t* thread_handles;
	
	thread_handles = malloc(4 * sizeof(pthread_t));

	clock_t t;
	float timeDiff;
	int i;

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


#include "physics.c"
#include "graphics.c"
#include "userInput.c"
#include "gameLogic.c"
