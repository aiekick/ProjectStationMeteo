#pragma once

#include <uv/include/uv11.hpp>
#include <memory>

class SensorHistory
{
private:
	std::unique_ptr<uv::Timer> m_Task;

public:
	void Init(uv::EventLoop& vEventLoop);

public: // singleton
	static SensorHistory* Instance()
	{
		static SensorHistory _instance;
		return &_instance;
	}
	SensorHistory() = default;
	SensorHistory(const SensorHistory&) = delete;
	SensorHistory& operator =(const SensorHistory&) = delete;
	~SensorHistory() = default;
};