#pragma once

namespace Pong
{

class Config
{
	int windowWidth;
	int windowHeight;

	Config(const Config&) = delete;
	Config(Config&&)      = delete;

public:
	Config();

	int GetWindowWidth() const;
	int GetWindowHeight() const;
};

} /* namespace Pong */