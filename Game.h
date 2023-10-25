#pragma once
#include "Box.h"
#include "Ball.h"
#include <vector>									// Adding in vector

class Game
{
	Ball ball;
	Box paddle;

	std::vector<Box> bricks;						// Creates a vector of bricks

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
};