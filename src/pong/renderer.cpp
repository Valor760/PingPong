#include "renderer.h"
#include "shaders.h"
#include "utils/exceptions.h"

namespace Pong
{

Renderer::Renderer(const glm::mat4& projection)
	: projection(projection)
{
	program = glCreateProgram();
	compileShaders();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	projLocation = glGetUniformLocation(program, "projection");
}

Renderer::~Renderer()
{
	glDeleteProgram(program);
}

void Renderer::compileShaders()
{
	/* TODO: Move shaders to a separate class */
	GLuint sVertex, sFragment;

	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &s_vertex, NULL);
	glCompileShader(sVertex);

	int success = -1;
	char log[1024];

	/* Check vertex shader compilation */
	glGetShaderiv(sVertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(sVertex, sizeof(log), NULL, log);
		throw Utils::PongException("VERTEX SHADER compile error: %s", log);
	}

	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &s_fragment, NULL);
	glCompileShader(sFragment);

	/* Check fragment shader compilation */
	glGetShaderiv(sFragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(sFragment, sizeof(log), NULL, log);
		throw Utils::PongException("FRAGMENT SHADER compile error: %s", log);
	}

	glAttachShader(program, sVertex);
	glAttachShader(program, sFragment);
	glLinkProgram(program);

	/* Check program linkage */
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, sizeof(log), NULL, log);
		throw Utils::PongException("PROGRAM LINK error: %s", log);
	}

	/* Delete shaders, because they are linked above */
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
}

void Renderer::RenderBegin()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(program);

	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void Renderer::RenderEnd()
{

}

void Renderer::SetMat4f(glm::mat4 mat, const char* name)
{
	PONG_ASSERT(name != nullptr);
	GLuint location = glGetUniformLocation(program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void Renderer::SetProjection(const glm::mat4& new_proj)
{
	projection = new_proj;
}

} /* namespace Pong */