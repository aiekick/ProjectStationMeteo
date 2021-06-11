#include "SensorHttpServer.h"

#include <stdint.h>
#include <string.h>
#include <stdexcept>

#include "SensorBME280.h"

void SensorHttpServer::Init(uv::EventLoop& vEventLoop)
{
	uv::http::HttpServer::SetBufferMode(uv::GlobalConfig::BufferMode::CycleBuffer);
	m_Server = std::make_unique<uv::http::HttpServer>(&vEventLoop);

	// default page
	//example:  127.0.0.1:80/
	m_Server->Get("/", std::bind(&SensorHttpServer::Defaultpage, this, std::placeholders::_1, std::placeholders::_2));

	//example:  127.0.0.1:80/sensor
	m_Server->Get("/sensor*", std::bind(&SensorHttpServer::SendSensorDatas, this, std::placeholders::_1, std::placeholders::_2));

	//example:  127.0.0.1:80/history:12
	m_Server->Get("/history:", std::bind(&SensorHttpServer::SendHistory, this, std::placeholders::_1, std::placeholders::_2));

	m_Server->setNewConnectCallback(std::bind(&SensorHttpServer::OnConnected, this, std::placeholders::_1));
	m_Server->setConnectCloseCallback(std::bind(&SensorHttpServer::OnDisConnected, this, std::placeholders::_1));

	uv::SocketAddr addr("0.0.0.0", 80, uv::SocketAddr::Ipv4);

	static uint32_t time_out_s = 60U * 5U; // 1m * 5 > 5m
	m_Server->setTimeout(time_out_s);

	m_Server->bindAndListen(addr);
}

////////////////////////////////////////////////////
//// PRIVATE ///////////////////////////////////////
////////////////////////////////////////////////////

void SensorHttpServer::OnConnected(std::weak_ptr<uv::TcpConnection> vPtr)
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

void SensorHttpServer::OnDisConnected(std::weak_ptr<uv::TcpConnection> vPtr)
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
void SensorHttpServer::Defaultpage(uv::http::Request& req, uv::http::Response* resp)
{
	resp->setVersion(uv::http::HttpVersion::Http1_1);
	resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
	std::string help = u8R"(
Welcome to BME280 HTTP Service.

You have two type of queries available :
* start a measure of the sensor : http://ip:port/sensor
* retrieve an history of last N hourly sensor measures :  http://ip:port/history:N (N msut be a number)

Happy Logging :)
)";
	resp->swapContent(help);
}

void SensorHttpServer::SendSensorDatas(uv::http::Request& req, uv::http::Response* resp)
{
	resp->setVersion(uv::http::HttpVersion::Http1_1);
	resp->setStatus(uv::http::Response::StatusCode::OK, "OK");
	resp->appendHead("Content-Type", "application/json");

	std::string json = SensorBME280::Instance()->GetSensorBME280DatasToJSON();
	
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

					json += SensorBME280::Instance()->GetSensorBME280DatasToJSON();
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
