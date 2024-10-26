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
	virtual void OnRender(Renderer& renderer) = 0;
};

class Square : public Figure
{
	// glm::vec2 topLeft;
	// glm::vec2 botRight;
	glm::vec2 position;

	void GenerateBuffers() override;

public:
	// Square(float x0, float y0, float x1, float y1, Renderer& renderer);
	// Square(glm::vec2 topLeft, glm::vec2 botRight, Renderer& renderer);
	Square(const glm::vec2& size, const glm::vec2& pos);

	void OnRender(Renderer& renderer) override;
	void Adjust(const glm::vec2& vec);
	glm::vec2 GetPosition() const;
};

} /* namespace Pong */