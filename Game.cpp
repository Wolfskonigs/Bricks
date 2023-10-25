#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	brick.clear();															// clears any bricks in the vector before looping

	for (int index = 0; index < 5; ++index)									// loops 5 times through to create 5 bricks
	{
		Box createNewBrick;													// declares a new box object to represent our bricks

		createNewBrick.width = 10;
		createNewBrick.height = 2;
		createNewBrick.x_position = index * 18;
		createNewBrick.y_position = 5;
		createNewBrick.doubleThick = true;
		createNewBrick.color = ConsoleColor::DarkGreen;

		brick.push_back(createNewBrick);									// Adds the created brick to our brick vector
	}

}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	for (int index = 0; index < brick.size(); ++index)								// Loops through the vector of bricks to draw each brick
	{
		brick[index].Draw();
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int index = 0; index < brick.size(); ++index)															// loops through each brick to check for collision
	{
		if (brick[index].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))		// checks the current brick contains the new position of the ball
		{
			brick[index].color = ConsoleColor(brick[index].color - 1);											// changes the color of the brick
			ball.y_velocity *= -1;																				// simulates ball bounce

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (brick[index].color == ConsoleColor::Black)
			{
				brick.erase(brick.begin() + index);
			}
		}
	}


	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset
	if (brick.empty())
	{
		ball.x_velocity = 0;
		ball.y_velocity = 0;

		std::cout << "\n\n\n";
		std::cout << "\t\t\t You win! Press 'R' to play again.\n";
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset

	if (ball.y_position >= WINDOW_HEIGHT)
	{
		ball.x_velocity = 0;
		ball.y_velocity = 0;

		std::cout << "\n\n\n";
		std::cout << "\t\t\t You Lose! Press 'R' to play again.\n";
	}
}
