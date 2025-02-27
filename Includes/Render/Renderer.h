#pragma once

#include "Core.h"
#include "Math/Vector2.h"
#include "Math/Vector2d.h"
#include <vector>

class ENGINE_API Renderer
{
public:
	Renderer(std::vector<std::vector<int>> grid, Vector2d position, \
		Vector2d direction, double width, double height);
	~Renderer() {};


	void Raycasting();
	void CheckDistance(double rx, double ry);
	void DrawLine(int i);
	void DrawInfo();
	void DrawMinimap();

	//setter
	void SetPosition(const Vector2d& newPosition);
	void SetDirection(const Vector2d& newDirection);
	void SetGrid(std::vector<std::vector<int>> grid) { this->grid = grid; };
	void SetStamina(int stamina) { this->stamina = stamina; };
	void SetTime(int time) { this->time = time; };

	void CheckObjectDistance(double rx, double ry);

	void SetObjectPosition(const Vector2d& newPosition) { objectPosition = newPosition; };
	void SetObjectWidth(double newWidth) { objectWidth = newWidth; };
private:
	std::vector<std::vector<int>> grid;
	Vector2d position;
	Vector2d direction;
	double width;
	double distance;
	double height;

	int side = 0;
	int objectValid = 0;
	int stamina;
	int time;

	Vector2d objectPosition;
	double objectWidth = 0.0;
	double objectDistance = 0.0;
};

