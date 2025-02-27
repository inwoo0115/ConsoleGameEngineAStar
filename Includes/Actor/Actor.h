#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2d.h"
#include "Math/Vector2.h"
// ������ �⺻ ��ü.
class ENGINE_API Actor : public RTTI
{
	// RTTI ����.
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level Ŭ������ friend�� ����.
	// private�� ������ �����ϵ���.
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// ���� ó�� �Լ�.
	virtual void Update(float delatTime);
	virtual void Draw();

	// Getter/Setter.
	virtual void SetPosition(const Vector2d& newPosition);
	virtual void SetDirection(const Vector2d& newDirection);
	inline Vector2d Position() const;
	inline Vector2d Direction() const;

	inline bool IsAcive() const { return isActive && !isExpired; }
	inline void SetActive(bool active) { isActive = active; }
	inline void Destroy() { isExpired = true; }

protected:
	// ������ ��ġ.
	Vector2d position;

	Vector2d direction;

	// ID(�ؽ�) / �̸� ��.
	// Ȱ��ȭ ���������� ��Ÿ���� ����.
	bool isActive;

	// ������ ���� ��û�� �ƴ��� ���θ� ��Ÿ���� ����.
	bool isExpired;
};