#include "Camera.h"
#include "Engine/Engine.h"
#include "Math/Vector2d.h"

Camera::Camera(Vector2d position, Vector2d direction, std::vector<std::vector<int>> grid, int stamina)
{
	SetPosition(position);
	SetDirection(direction);
	this->grid = grid;
	this->stamina = stamina;
}

void Camera::Update(float deltaTime)
{
	Super::Update(deltaTime);

	double x = 0.0, y = 0.0, speed = 0.03;

	//방향전환
	if (Engine::Get().GetKey(VK_RIGHT))
	{
		SetDirection(direction.VectorRotation(0.1));
	}
	else if (Engine::Get().GetKey(VK_LEFT))
	{
		SetDirection(direction.VectorRotation(-0.1));
	}


	//달리기
	if (Engine::Get().GetKey(VK_SPACE))
	{
		if (stamina > 10)
		{
			speed = 0.1;
			stamina -= 2;
		}
	}
	else
	{
		if (stamina < 300)
			stamina += 2;
	}


	//이동
	if (Engine::Get().GetKey(VK_UP))
	{
		x = position.x + direction.x * speed;
		y = position.y + direction.y * speed;
		if (grid[static_cast<int>(position.y)][static_cast<int>(x)] != 1)
		{
			position.x = x;
		}
		if (grid[static_cast<int>(y)][static_cast<int>(position.x)] != 1)
		{
			position.y = y;
		}
	}
	else if (Engine::Get().GetKey(VK_DOWN))
	{
		x = position.x - direction.x * speed;
		y = position.y - direction.y * speed;
		if (grid[static_cast<int>(position.y)][static_cast<int>(x)] != 1)
		{
			position.x = x;
		}
		if (grid[static_cast<int>(y)][static_cast<int>(position.x)] != 1)
		{
			position.y = y;
		}
	}

	//포탈 타기
	int currentPosition = grid[static_cast<int>(position.y)][static_cast<int>(position.x)];
	if (currentPosition > 2)
	{
		UsePortal(currentPosition);
	}
}

void Camera::UsePortal(int portal)
{
	for (int i = 0; i < grid.size(); ++i) {
		for (int j = 0; j < grid[i].size(); ++j) {
			if (grid[i][j] == portal) {
				if (i != static_cast<int>(position.y) || j != static_cast<int>(position.x))
				{
					//포탈과 안곂치게 탈출
					if (grid[i + 1][j] == 0)
					{
						SetPosition(Vector2d(j + 0.5, i + 1.5));
						SetDirection(Vector2d(-1, 0));
					}
					else if (grid[i][j + 1] == 0)
					{
						SetPosition(Vector2d(j + 1.5, i + 0.5));
						SetDirection(Vector2d(0, -1));
					}
					else if (grid[i - 1][j] == 0)
					{
						SetPosition(Vector2d(j + 0.5, i - 0.5));
						SetDirection(Vector2d(1, 0));
					}
					else if (grid[i][j - 1] == 0)
					{
						SetPosition(Vector2d(j - 0.5, i + 0.5));
						SetDirection(Vector2d(0, 1));
					}
					return;
				}
			}
		}
	}
}
