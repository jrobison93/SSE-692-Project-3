#include <pthread.h>

void initializeGame()
{
	// Initialize the ball
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
	ball.dx = 1;
	ball.dy = 1;

	player.height = HEIGHT / 4;
	player.width = WIDTH / 20;
	player.x = 10;
	player.y = (HEIGHT / 2) - (player.height / 2);

	ai.height = HEIGHT / 4;
	ai.width = WIDTH / 20;
	ai.x = WIDTH - 10;
	ai.y = (HEIGHT / 2) - (ai.height / 2);
	
}


void* updateGame(void* params)
{
	pthread_rwlock_rdlock(&ballLock);
	if(ball.x < 0)
	{
		pthread_rwlock_unlock(&ballLock);
		playerScore++;
		reset();
	}
	else if(ball.x + ball.width > WIDTH)
	{
		pthread_rwlock_unlock(&ballLock);
		aiScore++;
		reset();
	}
	else
	{
		pthread_rwlock_unlock(&ballLock);
	}
}

void reset()
{
	pthread_rwlock_wrlock(&ballLock);
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
	pthread_rwlock_unlock(&ballLock);
}
