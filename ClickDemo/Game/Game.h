#pragma once

#include "Engine/Engine.h"

class Game : public Engine
{
public:
	Game();
	~Game();

	void ToggleMenu();

	void TitleMenu();

	//�̱��� ���� �Լ�
	static Game& Get() { return *instance; }

	void SetConsoleScreenSizeInit();
	void SetConsoleEnableVTmode();
	void SetConsoleFontSize(int fontSizeX, int fontSizeY);

	void SetConsoleScreenSize(int width, int height);

	void SetCursorPosition(const Vector2& position);
	void SetConsoleTextColor(int color);

private:
	bool showMenu = false;

	//�� ����
	Level* menuLevel = nullptr;
	Level* backLevel = nullptr;

	// �̱��� ���� ��ü
	static Game* instance;
};