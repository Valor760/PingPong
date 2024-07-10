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

Square::Square(glm::vec2 size, glm::vec2 pos, Renderer& renderer)
	: renderer(renderer)
{
	vertices = {
		0.0f,   size.y,
		0.0f,   0.0f,
		size.x, size.y,
		size.x, 0.0f
	};

	position = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f));

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

void Square::Render()
{
	// glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model[LetterIdx::S]));
	// glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform[LetterIdx::S]));
	renderer.SetMat4f(position, "model");
	glBindVertexArray(VAO[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, vertices.size() / 2);
}

} /* namespace Pong */