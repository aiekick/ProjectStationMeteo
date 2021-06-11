#pragma once

#include <string>
#include <stdint.h>

struct SensorBME280DatasStruct
{
	uint64_t epoc = 0;
	float temp = 0.0f;
	float pres = 0.0f;
	float humi = 0.0f;
};

struct bme280_data;
struct bme280_dev;
class SensorBME280
{
private:
	std::string m_I2cBus;

public:
	bool GetSensorBME280Datas(SensorBME280DatasStruct* vSensorBME280DatasStruct);
	std::string ConvertSensorBME280DatasStructToJSON(const SensorBME280DatasStruct& vDatas);
	std::string GetSensorBME280DatasToJSON();

private:
    uint64_t GetCurrentEpochTime();

#ifdef UNIX
    void SaveSensorData(bme280_data* comp_data, SensorBME280DatasStruct* vSensorBME280DatasStruct);
	int8_t GetSensorBME280DataNormalMode(bme280_dev* dev, SensorBME280DatasStruct* vSensorBME280DatasStruct);
#endif

public: // singleton
	static SensorBME280* Instance(const std::string& vI2CBus = "")
	{
		static SensorBME280 _instance(vI2CBus);
		return &_instance;
	}
	SensorBME280(const std::string& vI2CBus);
	SensorBME280(const SensorBME280&) = delete;
	SensorBME280& operator =(const SensorBME280&) = delete;
	~SensorBME280() = default;
};