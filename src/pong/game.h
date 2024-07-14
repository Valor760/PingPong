#pragma once

#include "events.h"
#include "player.h"

#include <memory>

namespace Pong
{

class Game : public KeyEvent
{
	EventHandler& events;
	glm::vec2& windowSize;
	bool paused;
	/* TODO: Make a pointer for easier restart implementation */
	std::shared_ptr<Player> player;

public:
	Game(EventHandler& hdl, Renderer& renderer, glm::vec2& wnd_size);

	void OnUpdate(double dt);

	bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} /* namespace Pong */