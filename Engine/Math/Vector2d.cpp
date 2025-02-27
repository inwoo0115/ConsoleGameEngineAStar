#include "PreCompiledHeader.h"
#include "Vector2d.h"
#include <cmath>

Vector2d::Vector2d(double x, double y)
    : x(x), y(y)
{
}

Vector2d Vector2d::operator+(const Vector2d& other)
{
    return Vector2d(x + other.x, y + other.y);
}

Vector2d Vector2d::operator-(const Vector2d& other)
{
    return Vector2d(x - other.x, y - other.y);
}

bool Vector2d::operator==(const Vector2d& other)
{
    return x == other.x && y == other.y;
}

bool Vector2d::operator!=(const Vector2d& other)
{
    return x != other.x || y != other.y;
}

//벡터 회전 변환 (angle : 라디안)
Vector2d Vector2d::VectorRotation(double angle)
{
    double xpos = x * cos(angle) - y * sin(angle);
    double ypos = x * sin(angle) + y * cos(angle);
    return Vector2d(xpos, ypos);
}
