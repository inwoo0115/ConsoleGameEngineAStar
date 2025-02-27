#pragma once

#include "Level/Level.h"

class Renderer;
class Timer;
class Camera;

class GameLevel : public Level
{
	// RTTI Àû¿ë.
	RTTI_DECLARATIONS(GameLevel, Level)

public:
	GameLevel(int width, int height, const char* map);

	virtual void Update(float deltaTime) override;

	virtual void Draw() override;

private:
	std::vector<std::vector<int>> grid;

	Renderer* renderer;

	Timer* timer;

	int totalTime;
	int playTime;

	bool gameContinue = true;
};