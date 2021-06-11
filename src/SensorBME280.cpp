#include "SensorBME280.h"

#include <string.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <cstdint>
#include <chrono>
#include <ctime>

#define BUFFER_LENGTH 1024
static char buffer[BUFFER_LENGTH + 1] = "";

SensorBME280::SensorBME280(const std::string& vI2CBus) : m_I2cBus(vI2CBus) 
{

}

#ifdef UNIX

#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "bme280.h"

#define OVERSAMPLE_TEMP 2
#define OVERSAMPLE_PRES 2
#define OVERSAMPLE_HUM 2

struct identifier
{
    uint8_t dev_addr;
    int8_t fd;
};

int8_t SensorBME280::UserI2cRead(uint8_t reg_addr, uint8_t* data, uint32_t len, void* intf_ptr)
{
    auto id = *((struct identifier*)intf_ptr);
    write(id.fd, &reg_addr, 1);
    read(id.fd, data, len);
    return 0;
}

void SensorBME280::UserDelayUs(uint32_t period, void* intf_ptr)
{
    usleep(period);
}

int8_t SensorBME280::UserI2cWrite(uint8_t reg_addr, const uint8_t* data, uint32_t len, void* intf_ptr)
{
    auto id = *((identifier*)intf_ptr);
    auto buf = new uint8_t[len + 1];
    buf[0] = reg_addr;
    memcpy(buf + 1, data, len);
    if (write(id.fd, buf, len + 1) < (uint16_t)len)
    {
        return BME280_E_COMM_FAIL;
    }

    delete[] buf;
    return BME280_OK;
}

void SensorBME280::SaveSensorData(
    bme280_data* comp_data, 
    SensorBME280DatasStruct* vSensorBME280DatasStruct)
{
    if (vSensorBME280DatasStruct)
    {
#ifdef BME280_FLOAT_ENABLE
        vSensorBME280DatasStruct->temp = comp_data->temperature;
        vSensorBME280DatasStruct->pres = 0.01 * comp_data->pressure;
        vSensorBME280DatasStruct->humi = comp_data->humidity;
#else
    #ifdef BME280_64BIT_ENABLE
        vSensorBME280DatasStruct->temp = 0.01f * comp_data->temperature;
        vSensorBME280DatasStruct->pres = 0.0001f * comp_data->pressure;
        vSensorBME280DatasStruct->humi = 1.0f / 1024.0f * comp_data->humidity;
    #else
        vSensorBME280DatasStruct->temp = 0.01f * comp_data->temperature;
        vSensorBME280DatasStruct->pres = 0.01f * comp_data->pressure;
        vSensorBME280DatasStruct->humi = 1.0f / 1024.0f * comp_data->humidity;
    #endif
#endif

        // epoc time
        vSensorBME280DatasStruct->epoc = GetCurrentEpochTime();
    }
}

int8_t SensorBME280::GetSensorBME280DataNormalMode(
    bme280_dev* dev, 
    SensorBME280DatasStruct *vSensorBME280DatasStruct)
{
    int8_t rslt = -1;
    
    if (vSensorBME280DatasStruct)
    {
        /* Recommended mode of operation: Indoor navigation */
        dev->settings.osr_h = BME280_OVERSAMPLING_2X;
        dev->settings.osr_p = BME280_OVERSAMPLING_2X;
        dev->settings.osr_t = BME280_OVERSAMPLING_2X;
        dev->settings.filter = BME280_FILTER_COEFF_16;
        dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

        uint8_t settings_sel;
        settings_sel = BME280_OSR_PRESS_SEL;
        settings_sel |= BME280_OSR_TEMP_SEL;
        settings_sel |= BME280_OSR_HUM_SEL;
        settings_sel |= BME280_STANDBY_SEL;
        settings_sel |= BME280_FILTER_SEL;
        rslt = bme280_set_sensor_settings(settings_sel, dev);
        rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

        /* Delay while the sensor completes a measurement */
        double wait_time = 1.25 + (2.3 * OVERSAMPLE_TEMP) + ((2.3 * OVERSAMPLE_PRES) + 0.575) + ((2.3 * OVERSAMPLE_HUM) + 0.575);
        dev->delay_us(wait_time * 1000, dev->intf_ptr);
        
		struct bme280_data comp_data;
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);

        save_sensor_data(&comp_data, vSensorBME280DatasStruct);
    }

    return rslt;
}

bool SensorBME280::GetSensorBME280Datas(SensorBME280DatasStruct *vSensorBME280DatasStruct)
{
    struct identifier id;
    if ((id.fd = open(m_I2cBus.c_str(), O_RDWR)) < 0)
    {
        fprintf(stderr, "Failed to open the i2c bus %s\n", m_I2cBus.c_str());
        return false;
    }

    id.dev_addr = BME280_I2C_ADDR_PRIM;
    if (ioctl(id.fd, I2C_SLAVE, id.dev_addr) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
        return false;
    }

    struct bme280_dev dev;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;
    dev.intf_ptr = &id;

    int8_t rslt = bme280_init(&dev);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
        return false;
    }

    usleep(9000);

	rslt = getSensorBME280DataNormalMode(&dev, vSensorBME280DatasStruct);
    if (rslt != BME280_OK)
    {
        fprintf(stderr, "Failed to stream sensor data (code %+d).\n", rslt);
        return false;
    }

	return true;
}

#else

bool SensorBME280::GetSensorBME280Datas(SensorBME280DatasStruct* vSensorBME280DatasStruct)
{
    if (vSensorBME280DatasStruct)
    {
        vSensorBME280DatasStruct->epoc = GetCurrentEpochTime();

        // random on windows for tuning, since we not have the sensor
        //vSensorBME280DatasStruct->epoc = rand() % 100000;
        vSensorBME280DatasStruct->temp = (float)(rand() % 90) - 40.0f;
        vSensorBME280DatasStruct->pres = (float)(rand() % 1000) + 500.0f;
        vSensorBME280DatasStruct->humi = (float)(rand() % 70) + 30.0f;

        return true;
    }

    return false;
}

#endif

std::string SensorBME280::ConvertSensorBME280DatasStructToJSON(const SensorBME280DatasStruct& vDatas)
{
	int n = snprintf(buffer, BUFFER_LENGTH,
		"{\"epoc\":%u,\"temp\":%.5f,\"pres\":%.5f,\"humi\":%.5f}",
		vDatas.epoc, vDatas.temp, vDatas.pres, vDatas.humi);
	return std::string(buffer, n);
}

std::string SensorBME280::GetSensorBME280DatasToJSON()
{
    SensorBME280DatasStruct res;
    if (GetSensorBME280Datas(&res))
        return ConvertSensorBME280DatasStructToJSON(res);
    return "";
}

uint64_t SensorBME280::GetCurrentEpochTime()
{
    // epoc time
    const auto ct = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(ct.time_since_epoch()).count();
}