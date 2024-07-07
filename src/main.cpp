#include "pong/app.h"
#include "pong/utils/exceptions.h"
#include "pong/utils/log.h"

int main()
{
	try
	{
		Pong::MainApp app;
		app.Run();
	}
	catch(Pong::Utils::PongException& ex)
	{
		LOG_ERROR("Exception in main - %s", ex.what());
		return -1;
	}
	catch(...)
	{
		LOG_ERROR("Unhandled exception in main");
		return -1;
	}

	return 0;
}