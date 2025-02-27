#include "PreCompiledHeader.h"
#include "Vector2.h"
#include <cmath>

Vector2::Vector2(int x, int y)
    : x(x), y(y)
{
}

Vector2 Vector2::operator+(const Vector2& other)
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
    return Vector2(x - other.x, y - other.y);
}

bool Vector2::operator==(const Vector2& other)
{
    return x == other.x && y == other.y;
}

bool Vector2::operator!=(const Vector2& other)
{
    return x != other.x || y != other.y;
}

//벡터 회전 변환 (angle : 라디안)
Vector2 Vector2::VectorRotation(double angle)
{
    double xpos = x * cos(angle) - y * sin(angle);
    double ypos = x * sin(angle) + y * cos(angle);
    return Vector2(xpos, ypos);
}
