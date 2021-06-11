#include "SensorHttpServer.h"

#include <stdint.h>
#include <string.h>
#include <stdexcept>

#include "SensorBME280.h"

#include <uv/include/TcpConnection.hpp>

void OnConnected(std::weak_ptr<uv::TcpConnection> vPtr)
{
	if (!vPtr.expired())
	{
		auto p = vPtr.lock();
		if (p)
		{
			printf("Connected to %s\n", p->Name().c_str());
		}
	}
}

void OnDisConnected(std::weak_ptr<uv::TcpConnection> vPtr)
{
	if (!vPtr.expired())
	{
		auto p = vPtr.lock();
		if (p)
		{
			printf("DisConnected from %s\n", p->Name().c_str());
		}
	}
}

void SensorHttpServer::Run()
{
	uv::EventLoop loop;
	uv::http::HttpServer::SetBufferMode(uv::GlobalConfig::BufferMode::CycleBuffer);
	uv::http::HttpServer server(&loop);

	// default page
	//example:  127.0.0.1:80/
	server.Get("/", std::bind(&SensorHttpServer::Defaultpage, this, std::placeholders::_1, std::placeholders::_2));
	
	//example:  127.0.0.1:80/sensor
	server.Get("/sensor*", std::bind(&SensorHttpServer::SendSensorDatas, this, std::placeholders::_1, std::placeholders::_2));

	//example:  127.0.0.1:80/history:12
	server.Get("/history:", std::bind(&SensorHttpServer::SendHistory, this, std::placeholders::_1, std::placeholders::_2));

	server.setNewConnectCallback(std::bind(&OnConnected, std::placeholders::_1));
	server.setConnectCloseCallback(std::bind(&OnDisConnected, std::placeholders::_1));

	uv::SocketAddr addr("0.0.0.0", 80, uv::SocketAddr::Ipv4);
	server.setTimeout(60);
	server.bindAndListen(addr);

	loop.run();
}

////////////////////////////////////////////////////
//// PRIVATE ///////////////////////////////////////
////////////////////////////////////////////////////

void SensorHttpServer::Defaultpage(uv::http::Request& req, uv::http::Response* resp)
{
	resp->setVersion(uv::http::HttpVersion::Http1_1);
	resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
	std::string help = u8R"(
Welcome to BME280 HTTP Service.

You have two type of queries available :
- start a measure of the sensor : http://ip:port/sensor
- retrieve an history of last N hourly sensor measures :  http://ip:port/history:N (N msut be a number)

Happy Logging :)
)";
	resp->swapContent(help);
}

void SensorHttpServer::SendSensorDatas(uv::http::Request& req, uv::http::Response* resp)
{
	resp->setVersion(uv::http::HttpVersion::Http1_1);
	resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
	resp->appendHead("Content-Type", "application/json");
	std::string json = SensorBME280::Instance()->GetSensorBME280DatasToString();
	resp->swapContent(json);
}

void SensorHttpServer::SendHistory(uv::http::Request& req, uv::http::Response* resp)
{
	resp->setVersion(uv::http::HttpVersion::Http1_1);
	resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
	resp->appendHead("Content-Type", "application/json");

	// sqlite extract

	std::string json;
	auto countStr = req.getValue();
	if (!countStr.empty())
	{
		try
		{
			int count = atoi(countStr.c_str()); // atoi can raise an exception

			if (count)
			{
				json += "\"count\":" + countStr + ",\"history\":[\n";

				for (int i = 0; i < count; i++)
				{
					if (i)
						json += ",\n";

					json += SensorBME280::Instance()->GetSensorBME280DatasToString();
				}

				json += "]";
			}
		}
		catch (std::exception)
		{
			json.clear();
		}
	}

	if (json.empty())
	{
		json = "bad value for history count";
	}
	else
	{
		json = "{" + json + "}";
	}

	resp->swapContent(json);
}
