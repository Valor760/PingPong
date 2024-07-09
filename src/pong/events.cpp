#include "events.h"
#include "utils/exceptions.h"

namespace Pong
{

static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	EventHandler* inst = (EventHandler*)glfwGetWindowUserPointer(window);

	for(auto& obj : inst->keyCallbacks)
	{
		if(obj->processEvent(window, key, scancode, action, mods))
		{
			return;
		}
	}
}

static void WindowSizeCallback(GLFWwindow* window, int width, int height)
{
	EventHandler* inst = static_cast<EventHandler*>(glfwGetWindowUserPointer(window));

	for(auto& obj : inst->windowSizeCallbacks)
	{
		if(obj->processEvent(window, width, height))
		{
			/* TODO: Most probably all window callbacks should return false? */
			return;
		}
	}
}

EventHandler::EventHandler(GLFWwindow* window)
	: window(window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
	glfwSetKeyCallback(window, KeyCallback);
}

EventHandler::~EventHandler()
{
	glfwSetWindowUserPointer(window, nullptr);
	glfwSetWindowSizeCallback(window, nullptr);
	glfwSetKeyCallback(window, nullptr);
}

void EventHandler::RegisterCallback(KeyEvent* obj)
{
	PONG_ASSERT(obj != nullptr);
	keyCallbacks.push_back(obj);
}

void EventHandler::RegisterCallback(WindowSizeEvent* obj)
{
	PONG_ASSERT(obj != nullptr);
	windowSizeCallbacks.push_back(obj);
}

} /* namespace Pong */