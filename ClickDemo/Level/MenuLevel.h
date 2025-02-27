#pragma once

#include <vector>
#include <Windows.h>
#include "Level/Level.h"

struct MenuItem
{
	//이벤트 선언
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected)
	{
		//문자열 복사
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}
	~MenuItem()
	{
		delete[] text;
		text = nullptr;
	}

	// 메뉴에서 보여줄 텍스트
	char* text;
	// 선택했을떄 함수 저장하는 포인터
	OnSelected onSelected;
};

class MenuLevel : public Level
{
	RTTI_DECLARATIONS(MenuLevel, Level)

public:
	MenuLevel();
	~MenuLevel();

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

