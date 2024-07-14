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
	PlayerI(glm::vec2 size, glm::vec2 pos, Renderer& renderer);

	virtual void OnUpdate(double dt, bool paused) = 0;
};

class Player : public PlayerI,
			   public KeyEvent
{
	EventHandler& events;

	std::mutex eventLock;
	bool upActive;
	bool downActive;

public:
	Player(const glm::vec2& size, const glm::vec2& pos, Renderer& renderer, EventHandler& hdl);

	void OnUpdate(double dt, bool paused) override;

	bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} /* namespace Pong */