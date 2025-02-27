#pragma once

#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Math/Vector2d.h"
#include <vector>

class Node;
class Timer;

class Monster : public Actor
{
	RTTI_DECLARATIONS(Monster, Actor)

public:
	Monster(Vector2d position, Vector2d direction, Vector2d playerPosition, std::vector<std::vector<int>> grid);
	
	virtual void Update(float deltaTime) override;
	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
	void SetPlayerPosition(Vector2d newPlayerPosition) { this->playerPosition = newPlayerPosition; };
	std::vector<std::vector<int>> ExpandGrid(const std::vector<std::vector<int>>& grid);

	//쓰레드 실행 함수
	void AStarThread(Node* startNode, Node* goalNode, std::vector<Node*>& path, const std::vector<std::vector<int>>& astarGrid);

private:
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> astarGrid;
	Vector2d playerPosition;
	Timer* timer;
	std::vector<Node*> path;

	Timer* frame;
};

