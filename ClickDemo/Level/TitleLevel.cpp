#include "TitleLevel.h"
#include "DemoLevel.h"
#include "GameLevel.h"
#include "Game/Game.h"

TitleLevel::TitleLevel()
{
	items.emplace_back(new MenuItem("Astar demo", []() {Game::Get().LoadLevel(new DemoLevel("./Asset/map.txt")); }));
	items.emplace_back(new MenuItem("3D demo", []() {Game::Get().LoadLevel(new GameLevel(300, 150, "./Asset/stage1.txt")); }));
	items.emplace_back(new MenuItem("Quit Game", []() {Game::Get().QuitGame(); }));

	//메뉴 개수 저장
	itemCount = (int)items.size();
}

TitleLevel::~TitleLevel()
{
	for (MenuItem* item : items)
	{
		delete item;
	}
	items.clear();
}

void TitleLevel::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Game::Get().GetKeyDown(VK_UP))
	{
		currentSelectIndex = (currentSelectIndex - 1 + itemCount) % itemCount;
	}

	if (Game::Get().GetKeyDown(VK_DOWN))
	{
		currentSelectIndex = (currentSelectIndex + 1) % itemCount;
	}

	if (Game::Get().GetKeyDown(VK_RETURN))
	{
		items[currentSelectIndex]->onSelected();
	}
}



void TitleLevel::Draw()
{
	Super::Draw();

	//// 글씨 크기 설정
	//Game::Get().SetConsoleFontSize(32, 24);
	//Game::Get().SetConsoleScreenSize(60, 20);

	//메뉴 제목 출력
	Game::Get().Draw(Vector2(0, 0), "AStar Test", Color::White);

	for (int ix = 0; ix < itemCount; ++ix)
	{
		Game::Get().Draw(Vector2(0, ix + 3), items[ix]->text, (Color)(ix == currentSelectIndex ? selectedColor : unselectedColor));
	}
}
