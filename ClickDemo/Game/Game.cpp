#include "Game.h"
#include "Level/MenuLevel.h"
#include "Level/TitleLevel.h"

Game* Game::instance = nullptr;

Game::Game()
{
	//싱글톤 객체 설정
	instance = this;
	//메뉴레벨 생성
	menuLevel = new MenuLevel();
}

Game::~Game()
{
	// 씬 삭제 처리
	if (showMenu)
	{
		// Engine의 메인 레벨이 menu
		delete backLevel;
		backLevel = nullptr;
		mainLevel = nullptr;
	}
	else
	{
		// 메인레벨이 testlevel
		delete mainLevel;
		mainLevel = nullptr;
	}
	delete menuLevel;
	menuLevel = nullptr;
}

void Game::ToggleMenu()
{
	// 값 뒤집기
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

	// 콘솔 창 크기 최소화 (충돌 방지)
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
	// 콘솔 핸들 가져오기
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) {
		//std::cerr << "Error: Unable to get console handle" << std::endl;
		return;
	}

	// 콘솔 글꼴 정보 구조체 초기화
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	// 현재 콘솔 글꼴 정보 가져오기
	if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) {
		//std::cerr << "Error: Unable to get console font info" << std::endl;
		return;
	}

	wcscpy_s(cfi.FaceName, L"Cascadia Mono"); // 글꼴 이름 설정
	// 글꼴 크기 설정
	cfi.dwFontSize.X = fontSizeX; // 글자 너비
	cfi.dwFontSize.Y = fontSizeY; // 글자 높이
	wcscpy_s(cfi.FaceName, L"Cascadia Mono"); // 글꼴 이름 설정 (예: Consolas)

	// 글꼴 정보 설정
	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Game::SetConsoleScreenSize(int width, int height)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// 콘솔 화면 버퍼 크기 설정
	COORD bufferSize;
	bufferSize.X = width;  // 콘솔 버퍼의 너비
	bufferSize.Y = height; // 콘솔 버퍼의 높이

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		//std::cerr << "Error: Unable to get console screen buffer info." << std::endl;
		return;
	}

	// 최대 크기 확인
	int maxWidth = csbi.dwMaximumWindowSize.X;
	int maxHeight = csbi.dwMaximumWindowSize.Y;
	if (width > maxWidth || height > maxHeight) {
		//std::cerr << "Error: Window size exceeds maximum screen resolution." << maxWidth << " " << maxHeight << std::endl;
	}

	if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) {
		//std::cerr << "Error: Unable to set console screen buffer size." << std::endl;
		return;
	}

	// 콘솔 창 크기 설정
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

