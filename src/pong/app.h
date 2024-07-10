#pragma once
#include "config.h"
#include "window.h"
#include "renderer.h"

#include <memory>

namespace Pong
{

class MainApp
{
	Config conf;
	std::shared_ptr<Window> window;
	std::shared_ptr<Renderer> renderer;
	glm::mat4 projection;

public:
	MainApp();

	void Run();
};

} /* namespace Pong */