#pragma once

#include "utils/math.h"
#include "renderer.h"

#include <vector>

namespace Pong
{

class Figure
{
protected:
	GLuint VAO[1];
	GLuint VBO[1];
	std::vector<float> vertices;

protected:
	virtual void GenerateBuffers() = 0;

public:
	virtual void Render() = 0;
};

class Square : public Figure
{
	// glm::vec2 topLeft;
	// glm::vec2 botRight;
	Renderer& renderer;
	glm::vec2 position;

	void GenerateBuffers() override;

public:
	// Square(float x0, float y0, float x1, float y1, Renderer& renderer);
	// Square(glm::vec2 topLeft, glm::vec2 botRight, Renderer& renderer);
	Square(glm::vec2 size, glm::vec2 pos, Renderer& renderer);

	void Render() override;
	void Adjust(glm::vec2 vec);
	glm::vec2 GetPosition() const;
};

} /* namespace Pong */