#include <cstdio>

#include "SensorHttpServer.h"
#include <stdexcept>

int main(int argc, char** args)
{
	/*if (argc < 2)
	{
		printf("Syntax is : prog i2cBus port\n ex : prog /dev/i2c-1 48001");
		exit(1);
	}
	
	try
	{
		SensorHttpServer server;


	}
	catch (std::exception& ex)
	{

	}*/

	
	SensorHttpServer server;
	server.Run();

	return 0;
}
