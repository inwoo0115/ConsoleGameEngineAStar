#include "Engine/Engine.h"
#include "Level/DemoLevel.h"
#include "Game/Game.h"
#include "Level/TitleLevel.h"

int main()
{
	Game game;

	game.LoadLevel(new TitleLevel());
	game.Run();
}