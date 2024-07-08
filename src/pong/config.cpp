#include "config.h"

namespace Pong
{

/* TODO: Read from file */
Config::Config()
{
	windowWidth  = 800;
	windowHeight = 600;
}

int Config::GetWindowWidth() const
{
	return windowWidth;
}

int Config::GetWindowHeight() const
{
	return windowHeight;
}

} /* namespace Pong */