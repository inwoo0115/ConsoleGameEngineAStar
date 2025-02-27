#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	void TitleMenu();

	//½Ì±ÛÅæ Á¢±Ù ÇÔ¼ö
	static Game& Get() { return *instance; }

	void SetConsoleScreenSizeInit();
	void SetConsoleEnableVTmode();
	void SetConsoleFontSize(int fontSizeX, int fontSizeY);

	void SetConsoleScreenSize(int width, int height);

	void SetCursorPosition(const Vector2& position);
	void SetConsoleTextColor(int color);

private:
	bool showMenu = false;

	//¾À º¯¼ö
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// ½Ì±ÛÅæ ±¸Çö °´Ã¼
	static Game* instance;
};