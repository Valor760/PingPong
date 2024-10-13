#include "player.h"
#include "utils/log.h"
#include "collision.h"

namespace Pong
{

PlayerI::PlayerI(glm::vec2 size, glm::vec2 pos, Renderer& renderer)
	: platform(size, pos, renderer)
{
}

Player::Player(const glm::vec2& size, const glm::vec2& pos, Renderer& renderer, EventHandler& hdl)
	: PlayerI(size, pos, renderer),
	  events(hdl),
	  size(size),
	  upActive(false),
	  downActive(false)
{
	events.RegisterCallback(dynamic_cast<KeyEvent*>(this));
}

bool Player::processEvent([[maybe_unused]] GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mods)
{
	std::lock_guard lg(eventLock);

	if(key == GLFW_KEY_W || key == GLFW_KEY_UP)
	{
		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			upActive = true;
		}
		else if(action == GLFW_RELEASE)
		{
			upActive = false;
		}
	}

	if(key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
	{
		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			downActive = true;
		}
		else if(action == GLFW_RELEASE)
		{
			downActive = false;
		}
	}

	return false;
}

void Player::OnUpdate(double dt, bool paused)
{
	std::lock_guard lg(eventLock);

	if(!paused)
	{
		if((upActive && !downActive) || (downActive && !upActive))
		{
			float y_move = 300.0f * static_cast<float>(dt);
			glm::vec2 curr_pos = platform.GetPosition();
			glm::vec2 adjust = {0.0f, upActive ? y_move : -y_move};
			
			CalculateMaximumCollisionDistance(size, curr_pos, adjust);
			platform.Adjust(adjust);

			// if(upActive)
			// {
			// 	platform.Adjust(adjust);
			// }

			// if(downActive)
			// {
			// 	platform.Adjust({0.0f, -y_move});
			// }
		}
	}

	platform.Render();
}

} /* namespace Pong */