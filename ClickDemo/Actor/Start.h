#pragma once

#include "Actor/DrawableActor.h"
#include <vector>

class Start : public DrawableActor
{
public:
	Start(Vector2 newPosition, int width, int height, std::vector<std::vector<int>> grid);

	virtual void Update(float deltaTime) override;
	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
private:
	int width;
	int height;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> grid10;
};