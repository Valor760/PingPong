#include "app.h"
#include "utils/exceptions.h"
#include "utils/log.h"
#include "game.h"

#include <chrono>

namespace Pong
{

MainApp::MainApp()
	: conf()
{
	if(!glfwInit())
	{
		throw Utils::PongException("Failed to initialize GLFW");
	}

	window = std::make_shared<Window>(conf.GetWindowWidth(), conf.GetWindowHeight(), false, "Ping Pong");
	if(!window)
	{
		throw Utils::PongException("Failed to create window - not enough memory");
	}

	if(!gladLoadGL(glfwGetProcAddress))
	{
		throw Utils::PongException("Can't initialize GLAD");
	}

	const glm::vec2& wnd_size = window->GetSize();
	glm::mat4 projection = glm::ortho(0.0f, wnd_size.x, 0.f, wnd_size.y, 0.0f, -1.0f);

	renderer = std::make_shared<Renderer>(projection);
	if(!renderer)
	{
		throw Utils::PongException("Failed to create rederer - not enough memory");
	}

	glViewport(0, 0, static_cast<int>(wnd_size.x), static_cast<int>(wnd_size.y));
}

void MainApp::Run()
{
	auto prev_time = std::chrono::steady_clock::now();

	Game game(*renderer, *window);

	while(!glfwWindowShouldClose(*window))
	{
		glfwPollEvents();

		renderer->RenderBegin();

		/* First draw any GUI than game elements on top */
		/* In most cases this will draw a background while the game itself will draw its GUI */
		// Gui::LayoutManager::DrawLayout();
		const std::chrono::duration<double> delta_time = std::chrono::steady_clock::now() - prev_time;
		game.OnUpdate(delta_time.count());
		game.OnRender();
		prev_time = std::chrono::steady_clock::now();

		/* Render end */
		renderer->RenderEnd();
		glfwSwapBuffers(*window);
	}
}

bool MainApp::processEvent([[maybe_unused]] GLFWwindow* window, int width, int height)
{
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.f, static_cast<float>(height), 0.0f, -1.0f);
	renderer->SetProjection(projection);

	return false;
}

} /* namespace Pong */