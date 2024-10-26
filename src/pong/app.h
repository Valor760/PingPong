#pragma once
#include "config.h"
#include "window.h"
#include "renderer.h"

#include <memory>

namespace Pong
{

class MainApp : public WindowSizeEvent
{
	Config conf;
	std::shared_ptr<Window> window;
	std::shared_ptr<Renderer> renderer;

public:
	MainApp();

	void Run();

	bool processEvent(GLFWwindow* window, int width, int height);
};

} /* namespace Pong */