#include "app.h"
#include "utils/exceptions.h"
#include "utils/log.h"

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

	window = std::make_shared<Window>(conf.GetWindowWidth(), conf.GetWindowHeight(), true, "Ping Pong");
	if(!window)
	{
		throw Utils::PongException("Failed to create window - not enough memory");
	}

	if(!gladLoadGL(glfwGetProcAddress))
	{
		throw Utils::PongException("Can't initialize GLAD");
	}
}

void MainApp::Run()
{
	/* Black color */
	glClearColor(0, 0, 0, 1.0);
	auto prev_time = std::chrono::steady_clock::now();

	while(!glfwWindowShouldClose(*window))
	{
		glfwPollEvents();

		glm::vec2 wnd_size = window->GetSize();
		glViewport(0, 0, static_cast<int>(wnd_size.x), static_cast<int>(wnd_size.y));

		// /* First draw any GUI than game elements on top */
		// /* In most cases this will draw a background while the game itself will draw its GUI */
		// Gui::LayoutManager::DrawLayout();
		// if(m_CurrentGame)
		// {
		// 	const std::chrono::duration<double> delta_time = std::chrono::steady_clock::now() - prev_time;
		// 	m_CurrentGame->OnUpdate(delta_time.count());
		// }

		prev_time = std::chrono::steady_clock::now();

		glClear(GL_COLOR_BUFFER_BIT);

		/* Render end */
		glfwSwapBuffers(*window);
	}
}

} /* namespace Pong */