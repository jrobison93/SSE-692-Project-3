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

void reset()
{
	pthread_rwlock_wrlock(&ballLock);
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
	pthread_rwlock_unlock(&ballLock);
}

int checkGameState()
{
	pthread_rwlock_rdlock(&playerLock);
	if(player.score == 10)
	{
		pthread_rwlock_unlock(&playerLock);
		return 1;
	}
	pthread_rwlock_unlock(&playerLock);

	pthread_rwlock_rdlock(&aiLock);
	if(ai.score == 10)
	{
		pthread_rwlock_unlock(&aiLock);
		return -1;	
	}
	pthread_rwlock_unlock(&aiLock);

	return 0;

}

void* updateGame(void* params)
{
	pthread_rwlock_rdlock(&ballLock);
	if(ball.x < 0)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_wrlock(&playerLock);
		player.score++;
		pthread_rwlock_unlock(&playerLock);
		int game = checkGameState();
		if(game == 1)
		{
			// Player wins
			gameOver = 1;
		}
		else
		{
			reset();
		}
	}
	else if(ball.x + ball.width > WIDTH)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_wrlock(&aiLock);
		ai.score++;
		pthread_rwlock_unlock(&aiLock);
		int game = checkGameState();
		if(game == -1)
		{
			// AI wins
			gameOver = 1;
		}
		else
		{
			// Continue the game
			reset();
		}
	}
	else
	{
		pthread_rwlock_unlock(&ballLock);
	}
}
