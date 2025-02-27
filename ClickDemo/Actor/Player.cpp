#include "Player.h"
#include "Engine/Engine.h"


Player::Player(Vector2 newPosition, int width, int height, std::vector<std::vector<int>> grid)
	: DrawableActor("e")
{
	color = Color::Green;
	positionInt = newPosition;
	this->width = width;
	this->height = height;
	this->grid = grid;
}

void Player::Update(float deltaTime)
{
	DrawableActor::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_ESCAPE))
	{
		Engine::Get().QuitGame();
	}

	if (Engine::Get().GetKeyDown(VK_RBUTTON))
	{
		Vector2 newPosition = Engine::Get().MousePosition();
		if (newPosition.x < width - 1 && newPosition.y < height - 1 && newPosition.x > 0 && newPosition.y > 0\
			&& grid[newPosition.y][newPosition.x] != 2 && grid[newPosition.y][newPosition.x] != 1)
			positionInt = newPosition;
	}
}