// Changes the direction of the ball when a collision is detected
void changeDirection(int dx, int dy)
{
	ball.dx *= dx;
	ball.dy *= dy;
}

// Checks for collisions
void* checkCollisions(params)
{

	// Checks to see if the ball has collided with the player
	if(ball.x == player.x + player.width && ball.y + ball.height >= player.y && 
		ball.y <= player.y + player.height)
	{
		changeDirection( -1, 1);
		return;
	}
	else if((ball.y == player.y || ball.y == player.y + player.height)
		&& ball.x + ball.width >=player.x && ball.x <= player.x + player.width)
	{
		changeDirection(1, -1);
		return;
	}


	// Checks to see if the ball has collided with the ai
	if(ball.x == ai.x && ball.y + ball.height >= ai.y && 
		ball.y <= ai.y + ai.height)
	{
		changeDirection( -1, 1);
		return;
	}
	else if((ball.y == ai.y || ball.y == ai.y + ai.height)
		&& ball.x + ball.width >= ai.x && ball.x <= ai.x + ai.width)
	{
		changeDirection(1, -1);
		return;
	}



	// Checks to see if the ball has hit the top or bottom of the screen
	if(ball.y == 0 || ball.y + ball.height == HEIGHT) 
	{
		changeDirection( 1, -1);
		return;
	}
}


