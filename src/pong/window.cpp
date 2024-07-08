#include "window.h"
#include "utils/exceptions.h"
#include "utils/log.h"

namespace Pong
{

void WindowSizeCallback(GLFWwindow* window, int new_width, int new_height)
{
	Window* wnd = static_cast<Window*>(glfwGetWindowUserPointer(window));
	/* TODO: assert wnd != nullptr*/
	glm::vec2 prev_size = wnd->GetSize();
	
	LOG_DEBUG("Window size changed: [prev %dx%d] [new %dx%d]", prev_size.x, prev_size.y, new_width, new_height);

	wnd->SetSize({new_width, new_height});
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

	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, WindowSizeCallback);
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

} /* namespace Pong */