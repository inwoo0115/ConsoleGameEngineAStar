#pragma once

#include "Math/Vector2.h"

class Node
{
	friend class AStar;

public:
	Node(const Vector2& position = Vector2(), Node* parent = nullptr)
		: position(position), parent(parent)
	{
	}

	~Node() = default;

	Vector2 operator-(const Node& other)
	{
		return position - other.position;
	}

	bool operator==(const Node& other)
	{
		return position == other.position;
	}

	bool operator!=(const Node& other)
	{
		return position != other.position;
	}

	inline Vector2 Position() const { return position; };

	void SetPosition(Vector2 newPosition) { position = newPosition; };

private:
	Vector2 position;
	Node* parent = nullptr;
	float gCost = 0.0f;
	float hCost = 0.0f;
	float fCost = 0.0f;
};