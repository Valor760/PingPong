#pragma once

#include "events.h"
#include "player.h"

namespace Pong
{

class Game : public KeyEvent
{
	EventHandler& events;
	bool paused;
	/* TODO: Make a pointer for easier restart implementation */
	Player player;

public:
	Game(EventHandler& hdl, Renderer& renderer);

	void OnUpdate(double dt);

	bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} /* namespace Pong */