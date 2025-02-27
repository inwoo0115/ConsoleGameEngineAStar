#include "Monster.h"
#include "Engine/Timer.h"
#include "Algorithm/AStar.h"
#include "Algorithm/Node.h"
#include <thread>
#include <functional>

Monster::Monster(Vector2d position, Vector2d direction, Vector2d playerPosition, std::vector<std::vector<int>> grid)
{
	SetPosition(position);
	SetDirection(direction);
	SetPlayerPosition(playerPosition);
	this->grid = grid;
	this->astarGrid = ExpandGrid(grid);
	timer = new Timer(4);
	frame = new Timer(0.1);
}

void Monster::Update(float deltaTime)
{
	Super::Update(deltaTime);

	timer->Update(deltaTime);

	frame->Update(deltaTime);

	// ���� ���� �̵�
	//double x = 0.0, y = 0.0, speed = 0.03;

	//Vector2d targetDir = (playerPosition - position).Normalize();

	//double dot = direction.Dot(targetDir);
	//double angle = std::atan2(direction.Cross(targetDir), direction.Dot(targetDir));


	//Vector2d newDirection = direction.VectorRotation(angle);

	//x = position.x + newDirection.x * speed;
	//y = position.y + newDirection.y * speed;

	//if (grid[static_cast<int>(position.y)][static_cast<int>(x)] != 1)
	//{
	//	position.x = x;
	//}
	//if (grid[static_cast<int>(y)][static_cast<int>(position.x)] != 1)
	//{
	//	position.y = y;
	//}

	//AStar �̵�
	if (timer->IsTimeOut())
	{
		timer->Reset();
		if (!path.empty())
		{
			for (Node* node : path) {
				delete node;  // ���� �޸� ����
			}
			path.clear();
		}

		Node *startNode = new Node(Vector2((int)(position.x * 10), (int)(position.y * 10)), nullptr);
		Node *goalNode = new Node(Vector2((int)(playerPosition.x * 10), (int)(playerPosition.y * 10)), nullptr);

		// ������ ���
		// ��� �Լ� �����Ϳ� ��ü�� ���ε�
		std::thread aStarThread(std::bind(&Monster::AStarThread, this, startNode, goalNode, std::ref(path), std::cref(astarGrid)));
		aStarThread.detach(); // �Ǵ� aStarThread.join();  // join�� ������ ���Ḧ ��ٸ��ϴ�.
	}

	if (!path.empty() && frame->IsTimeOut())
	{
		frame->Reset();
		Node* nextNode = path.front();
		path.erase(path.begin());
		position.x = (double)(nextNode->Position().x) / 10;
		position.y = (double)(nextNode->Position().y) / 10;
	}
}

std::vector<std::vector<int>> Monster::ExpandGrid(const std::vector<std::vector<int>>& grid) {
	int oldRows = grid.size();
	int oldCols = grid[0].size();
	int newRows = oldRows * 10;
	int newCols = oldCols * 10;

	std::vector<std::vector<int>> newGrid(newRows, std::vector<int>(newCols));

	for (int i = 0; i < oldRows; ++i) {
		for (int j = 0; j < oldCols; ++j) {
			int value = grid[i][j];

			// (i, j) ��ġ�� ���� 10�� Ȯ��Ǿ� ���ο� ��ġ�� �Ҵ�
			for (int di = 0; di < 10; ++di) {
				for (int dj = 0; dj < 10; ++dj) {
					newGrid[i * 10 + di][j * 10 + dj] = value;
				}
			}
		}
	}
	return newGrid;
}

void Monster::AStarThread(Node* startNode, Node* goalNode, std::vector<Node*>& path,\
	const std::vector<std::vector<int>>& astarGrid) 
{
	AStar aStar;
	path = aStar.FindPath(startNode, goalNode, astarGrid, 1000000);
}
