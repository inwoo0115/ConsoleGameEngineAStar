#pragma once

#include <vector>
#include <Windows.h>
#include <Level/Level.h>
#include "MenuLevel.h"

class TitleLevel : public Level
{
	RTTI_DECLARATIONS(TitleLevel, Level)

public:
	TitleLevel();
	~TitleLevel();

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

private:
	int currentSelectIndex = 0;
	int selectedColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	int unselectedColor =
		FOREGROUND_RED | FOREGROUND_BLUE;

	//�޴� �����
	std::vector<MenuItem*> items;
	//������ ����
	int itemCount = 0;
};
