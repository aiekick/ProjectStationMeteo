#pragma once

#include <stdint.h>
#include <string>
#include <uv/include/uv11.hpp>

class SensorHttpServer
{
public:
	void Run();

private:
	void Defaultpage(uv::http::Request& req, uv::http::Response* resp);
	void SendSensorDatas(uv::http::Request& req, uv::http::Response* resp);
	void SendHistory(uv::http::Request& req, uv::http::Response* resp);
};