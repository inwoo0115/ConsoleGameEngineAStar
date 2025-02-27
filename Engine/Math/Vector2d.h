#pragma once

#include "Core.h"

class ENGINE_API Vector2d
{
public:
	Vector2d(double x = 0, double y = 0);
	~Vector2d() = default;

	// ������ �����ε�.
	Vector2d operator+(const Vector2d& other);
	Vector2d operator-(const Vector2d& other);
	bool operator==(const Vector2d& other);
	bool operator!=(const Vector2d& other);

	Vector2d VectorRotation(double angle);

	Vector2d Normalize() const {
		double len = std::sqrt(x * x + y * y);
		return { x / len, y / len };
	}

	double Dot(const Vector2d& other) const {
		return x * other.x + y * other.y;
	}

	double Cross(const Vector2d& other) const {
		return x * other.y - y * other.x;
	}
public:
	// x��ǥ / y��ǥ.
	double x = 0;
	double y = 0;
};