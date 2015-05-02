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
	ball.x = (WIDTH / 2) - (ball.width / 2);
	ball.y = (HEIGHT / 2) - (ball.height / 2);
}

void updateBall()
{
	ball.x += ball.dx;
	ball.y += ball.dy;
}

// Checks the player and ai's scores to see if the game has been won
int checkGameState()
{
	if(player.score == 10)
	{
		return 1;
	}

	if(ai.score == 10)
	{
		return -1;	
	}

	return 0;

}

void updateAI()
{
	if(ball.y > ai.y + ai.height)
	{
		ai.y++;
	}
	else if(ball.y + ball.height > ai.y)
	{
		ai.y--;	
	}
}

// Updates the game a fixed number of times a second
void* updateGame()
{

	// Sees if the ball has been scored on the by the player
	if(ball.x + ball.width > WIDTH)
	{
		player.score++;
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
		ai.score++;
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
		updateAI();
		updateBall();
	}
}
