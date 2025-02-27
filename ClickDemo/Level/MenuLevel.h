#pragma once

#include <vector>
#include <Windows.h>
#include "Level/Level.h"

struct MenuItem
{
	//�̺�Ʈ ����
	using OnSelected = void (*)();

	MenuItem(const char* text, OnSelected onSelected) : onSelected(onSelected)
	{
		//���ڿ� ����
		size_t length = strlen(text) + 1;
		this->text = new char[length];
		strcpy_s(this->text, length, text);
	}
	~MenuItem()
	{
		delete[] text;
		text = nullptr;
	}

	// �޴����� ������ �ؽ�Ʈ
	char* text;
	// ���������� �Լ� �����ϴ� ������
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

	//�޴� �����
	std::vector<MenuItem*> items;
	//������ ����
	int itemCount = 0;
};

