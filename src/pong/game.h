#pragma once

#include "events.h"
#include "player.h"
#include "window.h"

#include <memory>

namespace Pong
{

class Game : public KeyEvent
{
	EventHandler& events;
	Renderer& renderer;
	Window& window;
	bool paused;

	/* TODO: Make a pointer for easier restart implementation */
	std::shared_ptr<Player> player;

public:
	Game(Renderer& renderer, Window& window);

	void OnUpdate(double dt);
	void OnRender();

	bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} /* namespace Pong */