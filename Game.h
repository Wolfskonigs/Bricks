#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>									// Adds in vector for our vector of bricks

class Game
{
	Ball ball;
	Box paddle;

	std::vector<Box> brick;						// Creates a vector of bricks

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();

	enum GameState
	{
		PLAYING,
		WON,
		LOST
	};

	GameState currentState = PLAYING;
};