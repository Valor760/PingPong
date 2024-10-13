#include "collision.h"

#include <vector>
#include <mutex>
#include <algorithm>

namespace Pong
{

static std::vector<CollisionObj> collisions = {};
static std::mutex collisionLock;

void AddCollisionObject(const CollisionObj& obj)
{
	std::lock_guard lg(collisionLock);
	collisions.push_back(obj);
}

void RemoveCollisionObject(const CollisionObj& obj)
{
	std::lock_guard lg(collisionLock);

	std::erase(collisions, obj);
}

bool isCollistion(const CollisionObj& first, const CollisionObj& second)
{
	// collision x-axis?
	bool collisionX = first.position.x + first.size.x >= second.position.x &&
		second.position.x + second.size.x >= first.position.x;

	// collision y-axis?
	bool collisionY = first.position.y + first.size.y >= second.position.y &&
		second.position.y + second.size.y >= first.position.y;

	// collision only if on both axes
	return collisionX && collisionY;
}

bool CheckCollision(const glm::vec2& size, const glm::vec2& pos, const glm::vec2& adjust)
{
	std::lock_guard lg(collisionLock);

	for(const auto& obj : collisions)
	{
		CollisionObj second(size, pos + adjust);
		if(isCollistion(obj, second))
		{
			return true;
		}
	}

	return false;
}

void CalculateMaximumCollisionDistance(const glm::vec2& size, const glm::vec2& pos, glm::vec2& adjust)
{
	std::lock_guard lg(collisionLock);

	glm::vec2 tmp = adjust;

	for(const auto& obj : collisions)
	{
		CollisionObj second(size, pos + adjust);
		if(isCollistion(obj, second))
		{
			float x_offset = 0.0f;
			float y_offset = 0.0f;

			if(second.position.x >= obj.position.x)
			{
				x_offset = adjust.x - (obj.position.x + obj.size.x - second.position.x);
			}
			else
			{
				x_offset = adjust.x - (second.position.x + second.size.x - obj.position.x);
			}

			if(second.position.y >= obj.position.y)
			{
				y_offset = adjust.y - (obj.position.y + obj.size.y - second.position.y);
			}
			else
			{
				y_offset = adjust.y - (second.position.y + second.size.y - obj.position.y);
			}

			if(tmp.x > x_offset)
			{
				tmp.x = x_offset;
			}

			if(tmp.y > y_offset)
			{
				tmp.y = y_offset;
			}
		}
	}

	adjust = tmp;
}

} /* namespace Pong */