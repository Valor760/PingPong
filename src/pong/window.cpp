#include "window.h"
#include "utils/exceptions.h"
#include "utils/log.h"

#include <thread>
namespace Pong
{

bool Window::processEvent(GLFWwindow* _window, int _width, int _height)
{
	if(_window != window)
	{
		return false;
	}

	LOG_DEBUG("Window size changed: [prev %dx%d] [new %dx%d]", width, height, _width, _height);

	width = _width;
	height = _height;

	return false;
}

Window::Window(int width, int height, bool resizable, const std::string& title)
	: width(width), height(height)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, resizable);

	/* TODO: Maybe make funny titles like in terraria and minecraft? :) */
	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if(!window)
	{
		throw Utils::PongException("Failed to create window");
	}

	LOG_DEBUG("Created window: %p size=%dx%d", window, width, height);

	glfwMakeContextCurrent(window);

	events = std::make_shared<EventHandler>(window);
	if(!events)
	{
		throw Utils::PongException("Failed to allocate events");
	}

	events->RegisterCallback(dynamic_cast<WindowSizeEvent*>(this));
}

Window::~Window()
{
	glfwDestroyWindow(window);
}

glm::vec2 Window::GetSize() const
{
	return glm::vec2(width, height);
}

void Window::SetSize(glm::vec2 size)
{
	width = static_cast<int>(size.x);
	height = static_cast<int>(size.y);
}

Window::operator GLFWwindow*()
{
	return window;
}

EventHandler& Window::GetEventHandler() const
{
	return *events;
}

} /* namespace Pong */