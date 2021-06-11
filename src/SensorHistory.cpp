#include "SensorHistory.h"
#include "SensorBME280.h"
#include "MeasureDataBase.h"

void SensorHistory::Init(uv::EventLoop& vEventLoop)
{
	static uint64_t time_out_ms = 1000U * 10U; // 10s // 60U; // 1s * 60 > 10 s
	static uint64_t time_repeat_ms = time_out_ms;// * 60U; // 1 min * 60 > 1 h

	m_Task = std::make_unique<uv::Timer>(&vEventLoop, time_out_ms, time_repeat_ms, [](uv::Timer* ptr)
		{
			SensorBME280DatasStruct datas;
			if (SensorBME280::Instance()->GetSensorBME280Datas(&datas))
			{
				MeasureDataBase::Instance()->AddBME280SensorDatas(datas.epoc, datas.temp, datas.pres, datas.humi);
			}
		});
	m_Task->start();
}