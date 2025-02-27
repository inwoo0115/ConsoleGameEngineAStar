#include "Start.h"
#include "Engine/Engine.h"

Start::Start(Vector2 newPosition, int width, int height, std::vector<std::vector<int>> grid)
	: DrawableActor("s")
{
	color = Color::Red;
	positionInt = newPosition;
	this->width = width;
	this->height = height;
	this->grid = grid;
}

void Start::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (Engine::Get().GetKeyDown(VK_LBUTTON))
	{
		Vector2 newPosition = Engine::Get().MousePosition();
		if (newPosition.x < width - 1 && newPosition.y < height - 1 && newPosition.x > 0 && newPosition.y > 0\
			&& grid[newPosition.y][newPosition.x] != 3 && grid[newPosition.y][newPosition.x] != 1)
			positionInt = newPosition;
	}
}