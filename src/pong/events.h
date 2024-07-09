#pragma once

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <map>

namespace Pong
{

class KeyEvent
{
protected:
	KeyEvent() = default;
	~KeyEvent() = default;

public:
	virtual bool processEvent(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};

class WindowSizeEvent
{
protected:
	WindowSizeEvent() = default;
	~WindowSizeEvent() = default;

public:
	virtual bool processEvent(GLFWwindow* window, int width, int height) = 0;
};

class EventHandler
{
	GLFWwindow* window;

public:
	std::vector<KeyEvent*> keyCallbacks;
	std::vector<WindowSizeEvent*> windowSizeCallbacks;

	EventHandler(GLFWwindow* window);
	~EventHandler();

	void RegisterCallback(KeyEvent* obj);
	void RegisterCallback(WindowSizeEvent* obj);
};

} /* namespace Pong */