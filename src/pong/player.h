#pragma once

#include "figures.h"
#include "events.h"

#include <mutex>

namespace Pong
{

class PlayerI
{
protected:
	Square platform;

public:
	PlayerI(const glm::vec2& size, const glm::vec2& pos);

	virtual void OnUpdate(double dt) = 0;
};

class Player : public PlayerI,
			   public KeyEvent
{
	EventHandler& events;
	glm::vec2 size;

	std::mutex eventLock;
	bool upActive;
	bool downActive;

public:
	Player(const glm::vec2& size, const glm::vec2& pos, EventHandler& hdl);

	void OnUpdate(double dt) override;
	void OnRender(Renderer& renderer);

	bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} /* namespace Pong */