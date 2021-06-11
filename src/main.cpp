#include <cstdio>

#include "SensorHttpServer.h"
#include "SensorBME280.h"
#include "SensorHistory.h"

#include <stdexcept>

int main(int argc, char** args)
{
#ifdef UNIX
	if (argc < 2)
	{
		printf("Syntax is : prog i2cBus port\n ex : prog /dev/i2c-1");
		exit(1);
	}
	SensorBME280::Instance(args[1]);
#endif

	SensorHttpServer server;
	SensorHistory history;

	try
	{
		uv::EventLoop loop;

		server.Init(loop);
		history.Init(loop);

		loop.run();
	}
	catch (std::exception& ex)
	{
		printf("Err : %s", ex.what());
	}

	return 0;
}
