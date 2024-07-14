#include "game.h"
#include "utils/log.h"
#include "utils/exceptions.h"

namespace Pong
{

constexpr glm::vec2 PLATFORM_SIZE = {15.0f, 100.0f};

Game::Game(EventHandler& hdl, Renderer& renderer, glm::vec2& wnd_size)
	: events(hdl),
	  windowSize(wnd_size),
	  paused(false)
{
	glm::vec2 player_pos = {windowSize.x - PLATFORM_SIZE.x, (windowSize.y - PLATFORM_SIZE.y) / 2};
	player = std::make_shared<Player>(PLATFORM_SIZE, player_pos, renderer, events);
	if(!player)
	{
		throw Utils::PongException("Failed to create player - out of memory");
	}

	hdl.RegisterCallback(dynamic_cast<KeyEvent*>(this));
}

void Game::OnUpdate(double dt)
{
	if(player)
	{
		player->OnUpdate(dt, paused);
	}
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