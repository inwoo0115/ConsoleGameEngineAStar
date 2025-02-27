#include "GameLevel.h"
#include "Render/Renderer.h"
#include "Engine/Timer.h"
#include "Engine/Engine.h"
#include "Game/Game.h"
#include "TitleLevel.h"
#include "Actor/Camera.h"
#include "Math/Vector2d.h"
#include "Actor/Monster.h"

GameLevel::GameLevel(int width, int height, const char* map)
{
	grid = OpenMapFile(map);

	actors.push_back(new Camera(Vector2d(4, 4), Vector2d(0, 1), grid, width));
	renderer = new Renderer(grid, Vector2d(4, 4), Vector2d(0, 1), width, height);
	totalTime = width;
	playTime = width;
	timer = new Timer(0.3);

	//monster add
	actors.push_back(new Monster(Vector2d(8, 8), Vector2d(0, 1), Vector2d(4, 4), grid));
}

void GameLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	timer->Update(deltaTime);

	//1초 타이머
	if (timer->IsTimeOut())
	{
		if (playTime > 0)
		--playTime;
		timer->Reset();
	}

	if (Engine::Get().GetKeyDown('M'))
	{
		Game::Get().ToggleMenu();
	}

	if (!gameContinue && Engine::Get().GetKey(VK_ESCAPE))
	{
		//title menu로 전환
		Engine::Get().LoadLevel(new TitleLevel());
	}

}

void GameLevel::Draw()
{
	Super::Draw();

	if (gameContinue)
	{
		//rendering data update
		Camera* player = dynamic_cast<Camera*>(actors[0]);
		Monster* monster = dynamic_cast<Monster*>(actors[1]);
		renderer->SetPosition(player->Position());
		renderer->SetDirection(player->Direction());
		renderer->SetStamina(player->GetStamina());
		renderer->SetTime(playTime);

		monster->SetPlayerPosition(player->Position());
		renderer->SetObjectPosition(monster->Position());
		renderer->SetObjectWidth(0.5);

	
		renderer->Raycasting();


		// 시간 지났을 시 종료
		if (playTime < 2)
		{
			gameContinue = false;
		}

		// 출구에 왔을 시 종료 TODO: 플레이어 포지션으로 수정 필요
		if (grid[player->Position().y][player->Position().x] == 2)
		{
			gameContinue = false;
		}

		if (std::sqrt((monster->Position().x - player->Position().x) * (monster->Position().x - player->Position().x) + \
			(monster->Position().y - player->Position().y) * (monster->Position().y - player->Position().y)) < 0.5)
		{
			gameContinue = false;
			playTime = -50;

		}
	}
	else if (playTime >= 2)
	{
		Engine::Get().Draw(Vector2(0, 0), "Stage clear!", Color::PurPle);
		Engine::Get().Draw(Vector2(0, 3), "Press ESC to return to title", Color::PurPle);
	}
	else if (playTime >= 0)
	{
		Engine::Get().Draw(Vector2(0, 0), "Time over", Color::PurPle);
		Engine::Get().Draw(Vector2(0, 3), "You lose", Color::PurPle);
		Engine::Get().Draw(Vector2(0, 6), "Press ESC to return to title", Color::PurPle);
	}
	else if (playTime <= -50)
	{
		for (int i = 0; i < 150; ++i)
			Engine::Get().Draw(Vector2(0, i), "00000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
0000000000000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000000000000\
00000000000000000000000000000000000000000000000", Color::Red);
	}
}
