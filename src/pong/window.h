#pragma once
#include "events.h"
#include "utils/math.h"

#include <string>
#include <memory>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Pong
{

class Window : public WindowSizeEvent
{
	int width;
	int height;
	GLFWwindow* window;
	std::shared_ptr<EventHandler> events;

public:
	Window(int width, int height, bool resizable, const std::string& title);
	~Window();

	glm::vec2 GetSize() const;
	void SetSize(glm::vec2 size);

	EventHandler& getEventHandler() const;
	bool processEvent(GLFWwindow* _window, int _width, int _height) override;

	operator GLFWwindow*();
};

}; /* namespace Pong */