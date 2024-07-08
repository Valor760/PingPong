#pragma once
#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

namespace Pong
{

class Window
{
	int width;
	int height;
	GLFWwindow* window;

public:
	Window(int width, int height, bool resizable, const std::string& title);
	~Window();

	glm::vec2 GetSize() const;
	void SetSize(glm::vec2 size);

	operator GLFWwindow*();
};

}; /* namespace Pong */