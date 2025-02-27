#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/TitleLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	//�̱��� ��ü ����
	instance = this;
	//�޴����� ����
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	// �� ���� ó��
	if (showMenu)
	{
		// Engine�� ���� ������ menu
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// ���η����� testlevel
		delete mainLevel;
		mainLevel = nullptr;
	}
	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	// �� ������
	showMenu = !showMenu;

	if (showMenu)
	{
		backLevel = mainLevel;
		mainLevel = menuLevel;
	}
	else
	{
		mainLevel = backLevel;
	}
}

void Game::TitleMenu()
{
	showMenu = !showMenu;
	mainLevel = backLevel;
	backLevel = nullptr;
	LoadLevel(new TitleLevel());
}

void Game::SetConsoleScreenSizeInit()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// �ܼ� â ũ�� �ּ�ȭ (�浹 ����)
	SMALL_RECT tempWindow = { 0, 0, 1, 1 };
	if (!SetConsoleWindowInfo(hConsole, TRUE, &tempWindow)) {
		std::cerr << "Error: Unable to minimize console window size." << std::endl;
		return;
	}
}

void Game::SetConsoleEnableVTmode()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
}

void Game::SetConsoleFontSize(int fontSizeX, int fontSizeY)
{
	// �ܼ� �ڵ� ��������
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) {
		//std::cerr << "Error: Unable to get console handle" << std::endl;
		return;
	}

	// �ܼ� �۲� ���� ����ü �ʱ�ȭ
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// ���� �ܼ� �۲� ���� ��������
	if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
		//std::cerr << "Error: Unable to get console font info" << std::endl;
		return;
	}

	wcscpy_s(cfi.FaceName, L"Cascadia Mono"); // �۲� �̸� ����
	// �۲� ũ�� ����
	cfi.dwFontSize.X = fontSizeX; // ���� �ʺ�
	cfi.dwFontSize.Y = fontSizeY; // ���� ����
	wcscpy_s(cfi.FaceName, L"Cascadia Mono"); // �۲� �̸� ���� (��: Consolas)

	// �۲� ���� ����
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Game::SetConsoleScreenSize(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// �ܼ� ȭ�� ���� ũ�� ����
	COORD bufferSize;
	bufferSize.X = width;  // �ܼ� ������ �ʺ�
	bufferSize.Y = height; // �ܼ� ������ ����

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		//std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
		return;
	}

	// �ִ� ũ�� Ȯ��
	int maxWidth = csbi.dwMaximumWindowSize.X;
	int maxHeight = csbi.dwMaximumWindowSize.Y;
	if (width > maxWidth || height > maxHeight) {
		//std::cerr << "Error: Window size exceeds maximum screen resolution." << maxWidth << " " << maxHeight << std::endl;
	}

	if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) {
		//std::cerr << "Error: Unable to set console screen buffer size." << std::endl;
		return;
	}

	// �ܼ� â ũ�� ����
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;

	if (!SetConsoleWindowInfo(hConsole, TRUE, &windowSize)) {
		//std::cerr << "Error: Unable to set console window size." << std::endl;
		return;
	}
}

void Game::SetCursorPosition(const Vector2& position)
{
	static HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { static_cast<short>(position.x), static_cast<short>(position.y) };
	SetConsoleCursorPosition(handle, coord);
}

void Game::SetConsoleTextColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

