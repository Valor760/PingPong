#pragma once

#include "utils/math.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Pong
{

class Renderer
{
	GLuint program;

	glm::mat4 projection;
	GLuint projLocation;

	void compileShaders();

public:
	Renderer(const glm::mat4& projection);
	~Renderer();

	void RenderBegin();
	void RenderEnd();
	void SetMat4f(glm::mat4 mat, const char* name);
	void SetProjection(const glm::mat4& new_proj);
};

} /* namespace Pong */