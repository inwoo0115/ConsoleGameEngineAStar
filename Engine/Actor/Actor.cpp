#include "PreCompiledHeader.h"
#include "Actor.h"

#include "Core.h"

Actor::Actor()
	: isActive(true), isExpired(false)
{
}

Actor::~Actor()
{
}

void Actor::Update(float delatTime)
{
}

void Actor::Draw()
{
}

void Actor::SetPosition(const Vector2d& newPosition)
{
	position = newPosition;
}

void Actor::SetDirection(const Vector2d& newDirection)
{
	direction = newDirection;
}

inline Vector2d Actor::Position() const
{
	return position;
}

inline Vector2d Actor::Direction() const
{
	return direction;
}
