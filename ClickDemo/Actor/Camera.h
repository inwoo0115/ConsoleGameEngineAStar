#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Math/Vector2d.h"
#include <vector>

class Camera : public Actor
{
	RTTI_DECLARATIONS(Camera, Actor)

public:
	Camera(Vector2d position, Vector2d direction, std::vector<std::vector<int>> grid, int stamina);

	virtual void Update(float deltaTime) override;
	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
	int GetStamina() { return stamina; };
	void UsePortal(int portal);

private:
	std::vector<std::vector<int>> grid;
	int stamina;
};

