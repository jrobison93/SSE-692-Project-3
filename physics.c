// Changes the direction of the ball when a collision is detected
void changeDirection(int dx, int dy)
{
	pthread_rwlock_wrlock(&ballLock);
	ball.dx *= dx;
	ball.dy *= dy;
	pthread_rwlock_unlock(&ballLock);
}

// Checks for collisions
void* checkCollisions(void* params)
{

	// Checks to see if the ball has collided with the player
	pthread_rwlock_rdlock(&ballLock);
	pthread_rwlock_rdlock(&playerLock);
	if(ball.x == player.x + player.width && ball.y + ball.height >= player.y && 
		ball.y <= player.y + player.height)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_unlock(&playerLock);
		changeDirection( -1, 1);
		return;
	}
	else if((ball.y == player.y || ball.y == player.y + player.height)
		&& ball.x + ball.width >=player.x && ball.x <= player.x + player.width)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_unlock(&playerLock);
		changeDirection(1, -1);
		return;
	}
	pthread_rwlock_unlock(&playerLock);


	// Checks to see if the ball has collided with the ai
	pthread_rwlock_rdlock(&aiLock);
	if(ball.x == ai.x && ball.y + ball.height >= ai.y && 
		ball.y <= ai.y + ai.height)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_unlock(&aiLock);
		changeDirection( -1, 1);
		return;
	}
	else if((ball.y == ai.y || ball.y == ai.y + ai.height)
		&& ball.x + ball.width >= ai.x && ball.x <= ai.x + ai.width)
	{
		pthread_rwlock_unlock(&ballLock);
		pthread_rwlock_unlock(&aiLock);
		changeDirection(1, -1);
		return;
	}
	pthread_rwlock_unlock(&aiLock);



	// Checks to see if the ball has hit the top or bottom of the screen
	if(ball.y == 0 || ball.y + ball.height == HEIGHT) 
	{
		pthread_rwlock_unlock(&ballLock);
		changeDirection( 1, -1);
		return;
	}
	pthread_rwlock_unlock(&ballLock);
}


