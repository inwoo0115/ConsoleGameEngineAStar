#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Math/Vector2d.h"
#include "Math/Vector2.h"
// 레벨의 기본 물체.
class ENGINE_API Actor : public RTTI
{
	// RTTI 선언.
	RTTI_DECLARATIONS(Actor, RTTI)

	// Level 클래스를 friend로 선언.
	// private에 접근이 가능하도록.
	friend class Level;

public:
	Actor();
	virtual ~Actor();

	// 루프 처리 함수.
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
	// 액터의 위치.
	Vector2d position;

	Vector2d direction;

	// ID(해시) / 이름 값.
	// 활성화 상태인지를 나타내는 변수.
	bool isActive;

	// 액터의 제거 요청이 됐는지 여부를 나타내는 변수.
	bool isExpired;
};