#include "DemoLevel.h"
#include "Actor/Player.h"
#include "Actor/Start.h"
#include "Engine/Engine.h"
#include "Core.h"
#include "Algorithm/AStar.h"
#include "Algorithm/Node.h"
#include "Actor/DrawableActor.h"
#include "Engine/Timer.h"
#include "Game/Game.h"

DemoLevel::DemoLevel(const char* map)
{
	grid = OpenMapFile(map);

	for (int x = 0; x < grid[0].size(); ++x)
	{
		for (int y = 0; y < grid.size(); ++y)
		{
			if (grid[y][x] == 2)
			{
				startPosition.x = x;
				startPosition.y = y;
			}
			if (grid[y][x] == 3)
			{
				goalPosition.x = x;
				goalPosition.y = y;
			}
		}
	}
	DrawableActor* start = new Start(startPosition, grid[0].size(), grid.size(), grid);
	actors.push_back(start);
	DrawableActor* goal = new Player(goalPosition, grid[0].size(), grid.size(), grid);
	actors.push_back(goal);

	//�ִϸ��̼� Ÿ�̸�
	timer = new Timer(0);
}

void DemoLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	//Ÿ�̸� ������Ʈ
	timer->Update(deltaTime);

	Start* start = dynamic_cast<Start*>(actors[0]);
	Player* player = dynamic_cast<Player*>(actors[1]);

	start->SetGrid(grid);
	player->SetGrid(grid);
	startPosition.x = start->PositionInt().x;
	startPosition.y = start->PositionInt().y;
	goalPosition.x = player->PositionInt().x;
	goalPosition.y = player->PositionInt().y;


	//player, start position update in gird
	for (int x = 0; x < grid[0].size(); ++x)
	{
		for (int y = 0; y < grid.size(); ++y)
		{
			if (grid[y][x] == 2 || grid[y][x] == 3)
			{
				grid[y][x] = 0;
			}
		}
	}

	grid[startPosition.y][startPosition.x] = 2;
	grid[goalPosition.y][goalPosition.x] = 3;

	// ESC Ű�� �޴� ȭ��.
	if (Engine::Get().GetKeyDown('M'))
	{
		Game::Get().ToggleMenu();
	}

	if (Engine::Get().GetKeyDown(VK_SPACE))
	{
		timer->SetTime(30);
		timer->Reset();
		path.clear();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON) || Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		timer->SetTime(0);
		timer->Reset();
		path.clear();
	}
}

void DemoLevel::Draw()
{
	Super::Draw();

	// ���� ���� display
	DisplayGrid();

	if (startPosition != goalPosition && !timer->IsTimeOut())
	{
		// ���� ��ġ�� ��ǥ��ġ ���.
		Node* startNode = nullptr;
		Node* goalNode = nullptr;
		
		for (int x = 0; x < grid[0].size(); ++x)
		{
			if (startNode != nullptr && goalNode != nullptr)
			{
				break;
			}
			for (int y = 0; y < grid.size(); ++y)
			{
				if (startNode != nullptr && goalNode != nullptr)
				{
					break;
				}

				if (grid[y][x] == 2)
				{
					startNode = new Node(Vector2(x, y), nullptr);
					continue;
				}

				if (grid[y][x] == 3)
				{
					goalNode = new Node(Vector2(x, y), nullptr);
					continue;
				}
			}
		}

		// A* ��ü ����.
		AStar aStar;

		int t = (int)(timer->ElapsedTime() * 30.0);

		// ��� Ž��. // ��ΰ� ���� �ȵǾ��� ��� Ž�� ���� ���
		path = aStar.FindPath(startNode, goalNode, grid, t);

		// ��� ���� �Ǿ��� ��� ���
		if (!path.empty())
		{
			aStar.DisplayGridWithPath(grid, path);
			for (Node* node : path)
				delete node;  // ���� �޸� ����
			path.clear();
		}
	}
}


void DemoLevel::DisplayGrid()
{
	for (int y = 0; y < grid.size(); ++y)
	{
		for (int x = 0; x < grid[0].size(); ++x)
		{
			// ��ֹ�.
			if (grid[y][x] == 1)
			{
				Engine::Get().Draw(Vector2(x, y), "1", Color::Yellow);
			}
			// �� ����.
			else if (grid[y][x] == 0)
			{
				Engine::Get().Draw(Vector2(x, y), "0", Color::White);
			}
		}
	}
}
