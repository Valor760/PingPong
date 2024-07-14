#include "game.h"
#include "utils/log.h"

namespace Pong
{

constexpr glm::vec2 PLATFORM_SIZE = {15.0f, 100.0f};

Game::Game(EventHandler& hdl, Renderer& renderer)
	: events(hdl),
	  paused(false),
	  /* TODO: Pass screen width and height */
	  player(PLATFORM_SIZE, {800 - PLATFORM_SIZE.x, (600 - PLATFORM_SIZE.y) / 2}, renderer, events)
{
	hdl.RegisterCallback(dynamic_cast<KeyEvent*>(this));
}

void Game::OnUpdate(double dt)
{
	player.OnUpdate(dt, paused);
}

bool Game::processEvent([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		paused = !paused;
		LOG_DEBUG("Game was %spaused", paused ? "" : "un");
	}

	return false;
}

} /* namespace Pong */