#include <pthread.h>

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
	ball.x = WIDTH / 2 - (ball.width / 2);
	ball.y = HEIGHT / 2 - (ball.height / 2);
	pthread_rwlock_unlock(&ballLock);
}
