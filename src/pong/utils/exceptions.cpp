#include "exceptions.h"

#include <string.h>
#include <stdarg.h>

namespace Pong::Utils
{

PongException::PongException()
{
	err = "Unknown error";
}

PongException::PongException(const char* fmt, ...)
{
	err.resize(1024);

	va_list args;
	va_start(args, fmt);

	vsnprintf(err.data(), err.size(), fmt, args);

	va_end(args);
}

const char* PongException::what()
{
	return err.c_str();
}

}; /* namespace Pong::Utils */