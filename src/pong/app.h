#pragma once
#include "config.h"
#include "window.h"

#include <memory>

namespace Pong
{

class MainApp
{
	Config conf;
	std::shared_ptr<Window> window;

public:
	MainApp();

	void Run();
};

} /* namespace Pong */