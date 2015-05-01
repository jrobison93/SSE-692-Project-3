void initializeGame()
{
	// Initialize the ball
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
	ball.dx = 1;
	ball.dy = 1;

	// Initialize the player
	player.height = HEIGHT / 4;
	player.width = WIDTH / 20;
	player.x = 10;
	player.y = (HEIGHT / 2) - (player.height / 2);

	// Initialize the AI
	ai.height = HEIGHT / 4;
	ai.width = WIDTH / 20;
	ai.x = WIDTH - 10;
	ai.y = (HEIGHT / 2) - (ai.height / 2);
	
}

// Return the ball to the center of the screen
void resetBall()
{
	pthread_rwlock_wrlock(&ballLock);
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
	pthread_rwlock_unlock(&ballLock);
}

// Checks the player and ai's scores to see if the game has been won
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

void updateAI()
{
	pthread_rwlock_rdlock(&ballLock);
	pthread_rwlock_wrlock(&aiLock);
	if(ball.y > ai.y + ai.height)
	{
		ai.y++;
	}
	else if(ball.y + ball.height > ai.y)
	{
		ai.y--;	
	}
	pthread_rwlock_unlock(&aiLock);
	pthread_rwlock_unlock(&aiLock);
}

// Updates the game a fixed number of times a second
void* updateGame(void* params)
{

	// Sees if the ball has been scored on the by the player
	pthread_rwlock_rdlock(&ballLock);
	if(ball.x + ball.width > WIDTH)
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
			resetBall();
		}
	}
	// Sees if the ball has been scored by the AI
	else if(ball.x < 0)
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
			resetBall();
		}
	}
	else
	{
		pthread_rwlock_unlock(&ballLock);
		updateAI();
	}
}
