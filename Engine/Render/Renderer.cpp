#include "PreCompiledHeader.h"
#include "Renderer.h"
#include <cmath>
#include <Engine/Engine.h>

Renderer::Renderer(std::vector<std::vector<int>> grid, \
	Vector2d position, Vector2d direction, double width, double height) : \
	grid(grid), position(position), direction(direction), width(width), height(height), distance(0)
{
	stamina = static_cast<int>(width);
	time = static_cast<int>(width);
}

void Renderer::Raycasting()
{
	double i = 0, ratio = 0;
	Vector2d raydirection = Vector2d(0.0, 0.0);
	Vector2d plane = direction.VectorRotation(1.57);

	while (i < width)
	{
		ratio = 2 * i / width - 1;
		raydirection.x = direction.x + plane.x * ratio;
		raydirection.y = direction.y + plane.y * ratio;
		CheckDistance(raydirection.x, raydirection.y);
		CheckObjectDistance(raydirection.x, raydirection.y);
		DrawLine(static_cast<int>(i));
		++i;
	}
	DrawInfo();
	DrawMinimap();
}


//1이상 숫자에 충돌할떄까지 거리 측정
void Renderer::CheckDistance(double rx, double ry)
{
	int x = static_cast<int>(position.x);
	int y = static_cast<int>(position.y);
	double dx = std::abs(1.0 / rx);
	double dy = std::abs(1.0 / ry);
	int signX = 1, signY = 1;

	double distX = 0.0, distY = 0.0;

	if (rx < 0)
	{
		signX = -1;
		distX = (position.x - x) * dx;
	}
	else
	{
		signX = 1;
		distX = (x - position.x + 1.0) * dx;
	}
	if (ry < 0)
	{
		signY = -1;
		distY = (position.y - y) * dy;
	}
	else
	{
		signY = 1;
		distY = (y - position.y + 1.0) * dy;
	}

	while (1)
	{
		if (distX < distY)
		{
			distX += dx;
			x += signX;
			if (grid[y][x] == 1)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				side = 0;
				break;
			}
			else if (grid[y][x] == 2)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				side = 1;
				break;
			}
			else if (grid[y][x] > 2)
			{
				distance = (x - position.x + (1 - signX) / 2) / rx;
				side = 2;
				break;
			}
		}
		else
		{
			distY += dy;
			y += signY;
			if (grid[y][x] == 1)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				side = 0;
				break;
			}
			else if (grid[y][x] == 2)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				side = 1;
				break;
			}
			else if (grid[y][x] > 2)
			{
				distance = (y - position.y + (1 - signY) / 2) / ry;
				side = 2;
				break;
			}
		}
	}
}

//y축을 기준으로 한줄씩 거리에 비례하여 줄 그리기
void Renderer::DrawLine(int x)
{
	int heightInt = static_cast<int>(height);
	int lineHeight = static_cast<int>(heightInt / distance);

	int start = (-1) * lineHeight + heightInt / 2;
	if (start < 0)
		start = 0;
	int end = lineHeight + heightInt / 2;
	if (end >= heightInt)
		end = heightInt - 1;

	int objectstart = heightInt / 2 - 25 / objectDistance;
	int objectend = heightInt / 2 + 60 / objectDistance;
	for (int y = 0; y < heightInt; ++y)
	{
		if (y < start)
			Engine::Get().Draw(Vector2(x, y), "1", Color::White);
		else if (y > end)
		{
			Engine::Get().Draw(Vector2(x, y), "0", Color::Green);
		}
		else
		{
			if (side == 0)
				Engine::Get().Draw(Vector2(x, y), "0", Color::Blue);
			else if (side == 1)
				Engine::Get().Draw(Vector2(x, y), "0", Color::Yellow);
			else if (side == 2)
				Engine::Get().Draw(Vector2(x, y), "0", Color::PurPle);
		}
		if (objectValid == 1)
		{
			if (y > objectstart && y < objectend)
				Engine::Get().Draw(Vector2(x, y), "0", Color::Black);
		}
	}
}

void Renderer::DrawInfo()
{
	int heightInt = static_cast<int>(height);
	int widthInt = static_cast<int>(width);

	for (int i = 0; i < stamina; ++i)
	{
		for (int j = 0; j < 5; ++j)
			Engine::Get().Draw(Vector2(i, heightInt + j), "0", Color::Red);
	}
	for (int i = 0; i < time; ++i)
	{
		for (int j = 5; j < 10; ++j)
			Engine::Get().Draw(Vector2(i, heightInt + j), "0", Color::Blue);
	}
}

void Renderer::DrawMinimap()
{
	//60 30 (width, height)
	int gridWidth = grid[0].size();
	int gridHeight = grid.size();
	//미니맵 배경 그리기
	for (int i = 0; i < 30; ++i)
	{
		Engine::Get().Draw(Vector2(240, 120 + i), "000000000000000000000000000000000000000000000000000000000000", Color::White);
	}

	int minimapX = (int)(position.x) - 5;
	int minimapY = (int)(position.y) - 5;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			if (i + minimapX >= 0 && i + minimapX < gridWidth && j + minimapY >= 0 && j + minimapY < gridHeight)
			{
				for (int dj = 0; dj < 3; ++dj) {
					if (grid[j + minimapY][i + minimapX] == 1)
						Engine::Get().Draw(Vector2(i * 6 + 240, j * 3 + dj + 120), "000000", Color::Blue);
				}
			}
		}
	}
	Engine::Get().Draw(Vector2(270, 135), "000", Color::Green);
	Engine::Get().Draw(Vector2(270, 136), "000", Color::Green);

	double objectX = (objectPosition.x - position.x + 5.0) * 6.0;
	double objectY = (objectPosition.y - position.y + 5.0) * 3.0;

	if ((int)objectX + 1 > 0 && (int)objectX + 1 < 60 && (int)objectY + 1 > 0 && (int)objectY + 1 < 30)
	{
		Engine::Get().Draw(Vector2(240 + (int)objectX + 1, 120 + (int)objectY + 1), "000", Color::Black);
		Engine::Get().Draw(Vector2(240 + (int)objectX + 1, 120 + (int)objectY + 2), "000", Color::Black);
	}
}

void Renderer::SetPosition(const Vector2d& newPosition)
{
	this->position = newPosition;
}

void Renderer::SetDirection(const Vector2d& newDirection)
{
	this->direction = newDirection;
}

void Renderer::CheckObjectDistance(double rx, double ry)
{
	double dx = position.x;
	double dy = position.y;

	while (grid[(int)dy][(int)dx] != 1 && grid[(int)dy][(int)dx] != 2 && grid[(int)dy][(int)dx] != 3)
	{
		dx += rx / 10;
		dy += ry / 10;
		//object 범위 안에 있을 경우 거리 값 계산해서 리턴
		if (dx > objectPosition.x - objectWidth / 2 && dx < objectPosition.x + objectWidth / 2 && \
			dy < objectPosition.y + objectWidth / 2 && dy > objectPosition.y - objectWidth / 2)
		{
			objectDistance = std::sqrt((dx - position.x) * (dx - position.x) + (dy - position.y) * (dy - position.y));
			if (objectDistance < distance)
			{
				objectValid = 1;
			}
			else
				objectValid = 0;
			return;
		}
	}
	objectValid = 0;
}
