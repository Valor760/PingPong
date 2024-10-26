#include "game.h"
#include "utils/log.h"
#include "utils/exceptions.h"
#include "collision.h"

namespace Pong
{

constexpr glm::vec2 PLATFORM_SIZE = {15.0f, 100.0f};

Game::Game(Renderer& renderer, Window& window)
	: events(window.GetEventHandler()),
	  renderer(renderer),
	  window(window),
	  paused(false)
{
	const glm::vec2& window_size = window.GetSize();
	glm::vec2 player_spawn_pos = {window_size.x - PLATFORM_SIZE.x, (window_size.y - PLATFORM_SIZE.y) / 2};
	player = std::make_shared<Player>(PLATFORM_SIZE, player_spawn_pos, events);
	if(!player)
	{
		throw Utils::PongException("Failed to create player - out of memory");
	}

	events.RegisterCallback(dynamic_cast<KeyEvent*>(this));
}

void Game::OnUpdate(double dt)
{
	if(!paused)
	{
		if(player)
		{
			player->OnUpdate(dt);
		}
	}
}

void Game::OnRender()
{
	if(player)
	{
		player->OnRender(renderer);
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