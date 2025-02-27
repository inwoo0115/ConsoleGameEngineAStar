#pragma once

#include "Actor/DrawableActor.h"
#include <vector>

class Player : public DrawableActor
{
	RTTI_DECLARATIONS(Player, DrawableActor)

public:
	Player(Vector2 newPosition, int width, int height, std::vector<std::vector<int>> grid);

	virtual void Update(float deltaTime) override;

	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
private:
	int width;
	int height;
	std::vector<std::vector<int>> grid;
};