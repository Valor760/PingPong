#pragma once

#include "utils/math.h"

namespace Pong
{

class CollisionObj
{
public:
	glm::vec2 position;
	glm::vec2 size;

	CollisionObj(const glm::vec2& position, const glm::vec2& size)
		: position(position), size(size)
	{
	}

	bool operator==(const CollisionObj& other)
	{
		return position == other.position && size == other.size;
	}
};

void AddCollisionObject(const CollisionObj& obj);
void RemoveCollisionObject(const CollisionObj& obj);
bool CheckCollision(const glm::vec2& size, const glm::vec2& pos, const glm::vec2& adjust);
void CalculateMaximumCollisionDistance(const glm::vec2& size, const glm::vec2& pos, glm::vec2& adjust);

} /* namespace Pong */