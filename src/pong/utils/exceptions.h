#pragma once

#include <exception>
#include <string>

namespace Pong::Utils
{

class PongException : public std::exception
{
	std::string err;

public:
	PongException();
	PongException(const char* fmt, ...);

	const char* what();
};

} /* namespace Pong::Utils */