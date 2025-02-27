#pragma once

#include "Level/Level.h"
#include "Algorithm/Node.h"

class Timer;

class DemoLevel : public Level
{
	// RTTI Á¤ÀÇ.
	RTTI_DECLARATIONS(DemoLevel, Level)

public:
	DemoLevel(const char* map);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void DisplayGrid();
private:
	std::vector<std::vector<int>> grid;

	Vector2 startPosition;
	Vector2 goalPosition;

	std::vector<Node*> path;

	Timer* timer;
};