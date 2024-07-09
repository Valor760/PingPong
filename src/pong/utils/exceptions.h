#pragma once
#include "log.h"

#include <cstdlib>
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

#ifdef PONG_BUILD_DEBUG
#define PONG_ASSERT(expression) \
			if(!!!(expression)) { \
				LOG_ERROR("ASSERTION FAILED: %s", #expression); \
				std::abort(); \
			}
#else
#define PONG_ASSERT(expression) ((void)0)
#endif
} /* namespace Pong::Utils */