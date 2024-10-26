#include "figures.h"

namespace Pong
{

// Square::Square(glm::vec2 topLeft, glm::vec2 botRight, Renderer& renderer)
// 	: topLeft(topLeft), botRight(botRight)
// {
// 	// vertices = {topLeft.x, topLeft.y, botRight.x, botRight.y};
// 	// vertices = {-0.75, 0.75, 0.75, -0.75, -0.75, -0.75};
// 	vertices = {200, 200, 600, 400, 200, 400, 400, 200};
// }

Square::Square(const glm::vec2& size, const glm::vec2& pos)
	: position(pos)
{
	vertices = {
		0.0f,   size.y,
		0.0f,   0.0f,
		size.x, size.y,
		size.x, 0.0f
	};

	GenerateBuffers();
}

void Square::GenerateBuffers()
{
	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);

	glBindVertexArray(VAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Square::OnRender(Renderer& renderer)
{
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
	renderer.SetMat4f(model, "model");
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLuint>(vertices.size() / 2));
}

void Square::Adjust(const glm::vec2& vec)
{
	position += vec;
}

glm::vec2 Square::GetPosition() const
{
	return position;
}

} /* namespace Pong */