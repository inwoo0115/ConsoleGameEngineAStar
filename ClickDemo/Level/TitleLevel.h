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

	//메뉴 저장소
	std::vector<MenuItem*> items;
	//아이템 개수
	int itemCount = 0;
};
