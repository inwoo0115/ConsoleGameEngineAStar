#include "AStar.h"
#include "Node.h"
#include "Math/Vector2.h"
#include "Engine/Engine.h"

#include <iostream>

AStar::AStar()
	: startNode(nullptr), goalNode(nullptr)
{
}

AStar::~AStar()
{
	// �޸� ����.
	for (Node* node : openList)
	{
		SafeDelete(node);
	}
	openList.clear();

	for (Node* node : closedList)
	{
		SafeDelete(node);
	}
	closedList.clear();

	for (Node* node :deleteList)
	{
		SafeDelete(node);
	}
	deleteList.clear();
}

std::vector<Node*> AStar::FindPath(Node* startNode, Node* goalNode, const std::vector<std::vector<int>>& grid, int time)
{
	this->startNode = startNode;
	this->goalNode = goalNode;

	// ���� ��带 ���� ����Ʈ(OpenList)�� �߰�.
	openList.emplace_back(startNode);

	// �����¿� �� �밢�� �̵� ����� ���
	std::vector<Direction> directions =
	{
		// �ϻ���� �̵�.
		{ 0, 1, 1.0f }, { 0, -1, 1.0f }, { 1, 0, 1.0f }, { -1, 0, 1.0f },

		// �밢�� �̵�.
		{ 1, 1, 1.414f }, { 1, -1, 1.414f }, { -1, 1, 1.414f }, { -1, -1, 1.414f }
	};

	// �̿� ��� Ž�� (���� ����Ʈ�� ��� ���� ���� ���� �ݺ�).
	while (!openList.empty() && time)
	{
		--time;
		// ���� ���� ����Ʈ���� fCost�� ���� ���� ��� �˻�.
		Node* lowestNode = openList[0];
		for (Node* node : openList)
		{
			if (node->fCost < lowestNode->fCost)
			{
				lowestNode = node;
			}
		}

		// fCost�� ���� ���� ��带 ���� ���� ����.
		Node* currentNode = lowestNode;

		// ���� ��尡 ��ǥ ������� Ȯ�� �� ������ ����.
		if (IsDestination(currentNode))
		{
			return ConstructPath(currentNode);
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ���� ����.
		for (int ix = 0; ix < static_cast<int>(openList.size()); ++ix)
		{
			if (*openList[ix] == *currentNode)
			{
				openList.erase(openList.begin() + ix);
				break;
			}
		}

		// �湮 ó���� ���� ���� ��带 ���� ����Ʈ�� �߰�.
		// �̹� ���� ��忡 �ִ� ������� Ȯ�� �Ŀ� ������ �߰�.
		bool isNodeInList = false;
		for (Node* node : closedList)
		{
			if (*node == *currentNode)
			{
				isNodeInList = true;
				break;
			}
		}

		if (isNodeInList)
		{
			continue;
		}

		closedList.emplace_back(currentNode);

		// �̿� ��� �湮(Ž��). (��/��/��/�� ���ʷ� �湮).
		for (const Direction& direction : directions)
		{
			// ������ �̵��� ��ġ ����.
			int newX = currentNode->position.x + direction.x;
			int newY = currentNode->position.y + direction.y;

			// �׸��� ���̸� ����.
			if (!IsInRange(newX, newY, grid))
			{
				continue;
			}

			// �̵��� ��ġ�� ��ֹ��� ��쿡�� ����.
			if (grid[newY][newX] == 1)
			{
				continue;
			}

			// �̹� �湮�� ����� ��� ����.
			if (HasVisited(newX, newY, currentNode->gCost + direction.cost))
			{
				continue;
			}

			// �湮�� ���� �̿� ��� ����.
			// �湮�� ����� gCost, hCost, fCost ���.
			Node* neighborNode = new Node(Vector2(newX, newY), currentNode);
			neighborNode->gCost = currentNode->gCost + direction.cost;
			neighborNode->hCost = CalculateHeuristic(neighborNode, goalNode);
			neighborNode->fCost = neighborNode->gCost + neighborNode->hCost;

			// �̿� ��尡 ���� ����Ʈ�� �ִ��� Ȯ��.
			Node* openListNode = nullptr;
			for (Node* node : openList)
			{
				if (*node == *neighborNode)
				{
					openListNode = node;
					break;
				}
			}

			// �̿� ��尡 ���� ����Ʈ�� ���� ���, �湮�� ���� ���� ����Ʈ�� �߰�.
			// �̿� ��尡 ���� ����Ʈ�� �ִٸ�, gCost�� fCost�� ���� �� ���� ��쿡 ���� ����Ʈ�� �߰�.
			if (openListNode == nullptr
				|| neighborNode->gCost < openListNode->gCost
				|| neighborNode->fCost < openListNode->fCost)
			{
				openList.emplace_back(neighborNode);
			}
			else
			{
				//SafeDelete(neighborNode);
				deleteList.emplace_back(neighborNode);
			}
		}
	}

	DisplayGridWithoutPath(grid);

	return {};
}

std::vector<Node*> AStar::ConstructPath(Node* goalNode)
{
	// ��ǥ ��� ����, �θ� ��带 ���� �������ϸ鼭 ��� ��� ����.
	std::vector<Node*> path;
	Node* currentNode = goalNode;
	while (currentNode != nullptr)
	{
		path.emplace_back(currentNode);
		currentNode = currentNode->parent;
	}

	std::reverse(path.begin(), path.end());

	// ���� �����ϱ�
	std::vector<Node*> deepCopiedPath;
	for (Node* node : path) {
		deepCopiedPath.push_back(new Node(*node));  // Node ��ü�� ���� �Ҵ��ϰ� ����
	}

	//return path;
	return deepCopiedPath;
}

float AStar::CalculateHeuristic(Node* currentNode, Node* goalNode)
{
	// ���� ����� ��ġ���� ��ǥ ��ġ������ �Ÿ��� �޸���ƽ ������ ���.
	Vector2 diff = *currentNode - *goalNode;
	return static_cast<float>(std::sqrt(std::pow(diff.x, 2) + std::pow(diff.y, 2)));
}

bool AStar::IsInRange(int x, int y, const std::vector<std::vector<int>>& grid)
{
	// x, y ������ ����� false ��ȯ.
	if (x < 0 || x >= grid[0].size() || y < 0 || y >= grid.size())
	{
		return false;
	}

	// ����� �ʾ����� true ��ȯ.
	return true;
}

bool AStar::HasVisited(int x, int y, float gCost)
{
	// ���� ����Ʈ�� ���� ����Ʈ�� �̹� �ش� ��ġ�� ��尡 ������ �湮�� ������ �Ǵ�.
	for (int ix = 0; ix < static_cast<int>(openList.size()); ++ix)
	{
		Node* node = openList[ix];
		if ((node->position.x == x && node->position.y == y))
		{
			// ��ġ�� ����, ����� �� ũ�� �湮�� ������ ���� ������ �湮�ߴٰ� �Ǵ�.
			if (gCost > node->gCost)
			{
				return true;
			}

			// ��ġ�� ������, ����� ���� ���, �湮�� �ʿ䰡 �����Ƿ�, ������ ��� ����.
			else
			{
				deleteList.push_back(*(openList.begin() + ix));
				openList.erase(openList.begin() + ix);
				//SafeDelete(node);
			}
		}
	}

	for (int ix = 0; ix < static_cast<int>(closedList.size()); ++ix)
	{
		Node* node = closedList[ix];
		if ((node->position.x == x && node->position.y == y))
		{
			// ��ġ�� ����, ����� �� ũ�� �湮�� ������ ���� ������ �湮�ߴٰ� �Ǵ�.
			if (gCost > node->gCost)
			{
				return true;
			}

			// ��ġ�� ������, ����� ���� ���, �湮�� �ʿ䰡 �����Ƿ�, ������ ��� ����.
			else
			{
				deleteList.push_back(*(closedList.begin() + ix));
				closedList.erase(closedList.begin() + ix);
				//SafeDelete(node);
			}
		}
	}

	// ����Ʈ�� ������ �湮���� ���� ������ �Ǵ�.
	return false;
}

bool AStar::IsDestination(Node* node)
{
	// ����� ��ġ�� ���� ������ ��.
	return *node == *goalNode;
}

void AStar::DisplayGridWithPath(std::vector<std::vector<int>> grid, const std::vector<Node*>& path)
{
	//������ ��� ǥ��
	//for (const Node* node : path)
	//{
	//	// ��δ� '4'�� ǥ��.
	//	if (node->Position() != startNode->Position() && node->Position() != goalNode->Position())
	//		grid[node->position.y][node->position.x] = 4;
	//}
	for (auto it = path.rbegin(); it != path.rend(); ++it)
	{
		const Node* node = *it;  // ���� �ݺ����� �� ��������

		if (node->Position() != startNode->Position() && node->Position() != goalNode->Position())
		{
			Engine::Get().Draw(Vector2(node->position.x, node->position.y), "*", Color::Blue);
			grid[node->position.y][node->position.x] = 4;
		}
	}


	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				//std::cout << "1 ";
				Engine::Get().Draw(Vector2(x, y), "1", Color::Yellow);
			}

			// ���.
			//else if (grid[y][x] == 4)
			//{
			//	//std::cout << "* ";
			//	Engine::Get().Draw(Vector2(x, y), "*", Color::Blue);
			//}

			// �� ����.
			else if (grid[y][x] == 0)
			{
				//std::cout << "0 ";
				Engine::Get().Draw(Vector2(x, y), "0", Color::White);
			}
		}
	}
}

void AStar::DisplayGridWithoutPath(std::vector<std::vector<int>> grid) 
{
	//������ ��� ǥ��
	for (const Node* node : openList)
	{
		// ��δ� '4'�� ǥ��.
		if (node->Position() != startNode->Position() && node->Position() != goalNode->Position())
			grid[node->position.y][node->position.x] = 4;
	}

	for (const Node* node : closedList)
	{
		// ��δ� '4'�� ǥ��.
		if (node->Position() != startNode->Position() && node->Position() != goalNode->Position())
			grid[node->position.y][node->position.x] = 4;
	}

	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				Engine::Get().Draw(Vector2(x, y), "1", Color::Yellow);
			}

			// ���.
			else if (grid[y][x] == 4)
			{
				Engine::Get().Draw(Vector2(x, y), "#", Color::PurPle);
			}

			// �� ����.
			else if (grid[y][x] == 0)
			{
				Engine::Get().Draw(Vector2(x, y), "0", Color::White);
			}
		}
	}
}