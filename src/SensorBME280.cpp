#include "SensorBME280.h"

#include <string.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFFER_LENGTH 1024
static char buffer[BUFFER_LENGTH + 1] = "";

SensorBME280::SensorBME280(const std::string& vI2CBus) : m_I2cBus(vI2CBus) {}

#ifdef UNIX
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include "bme280.h"

struct identifier
{
    uint8_t dev_addr;
    int8_t fd;
};

int8_t user_i2c_read(uint8_t reg_addr, uint8_t* data, uint32_t len, void* intf_ptr)
{
    struct identifier id;
    id = *((struct identifier*)intf_ptr);
    write(id.fd, &reg_addr, 1);
    read(id.fd, data, len);
    return 0;
}

void user_delay_us(uint32_t period, void* intf_ptr)
{
    usleep(period);
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t* data, uint32_t len, void* intf_ptr)
{
    uint8_t* buf;
    struct identifier id;
    id = *((struct identifier*)intf_ptr);
    buf = malloc(len + 1);
    buf[0] = reg_addr;
    memcpy(buf + 1, data, len);
    if (write(id.fd, buf, len + 1) < (uint16_t)len)
    {
        return BME280_E_COMM_FAIL;
    }

    free(buf);
    return BME280_OK;
}

void print_sensor_data(
    struct bme280_data* comp_data, 
    SensorBME280DatasStruct* vSensorBME280DatasStruct)
{
    float temp, press, hum;

#ifdef BME280_FLOAT_ENABLE
    temp = comp_data->temperature;
    press = 0.01 * comp_data->pressure;
    hum = comp_data->humidity;
#else
    #ifdef BME280_64BIT_ENABLE
        temp = 0.01f * comp_data->temperature;
        press = 0.0001f * comp_data->pressure;
        hum = 1.0f / 1024.0f * comp_data->humidity;
    #else
        temp = 0.01f * comp_data->temperature;
        press = 0.01f * comp_data->pressure;
        hum = 1.0f / 1024.0f * comp_data->humidity;
    #endif
#endif

    //printf("Chip ID     :", chip_id
    //printf("Version     :", chip_version
    printf("Temperature : %.1f C\n", temp);
    printf("Pressure : %.1f hPa\n", press);
    printf("Humidity : %.1f %%\n", hum);
}

#define OVERSAMPLE_TEMP 2
#define OVERSAMPLE_PRES 2
#define OVERSAMPLE_HUM 2

int8_t getSensorBME280DataNormalMode(struct bme280_dev* dev, SensorBME280DatasStruct *vSensorBME280DatasStruct)
{
    int8_t rslt = -1;
    
    if (vSensorBME280DatasStruct)
    {
        uint8_t settings_sel;
        struct bme280_data comp_data;

        /* Recommended mode of operation: Indoor navigation */
        dev->settings.osr_h = BME280_OVERSAMPLING_2X;
        dev->settings.osr_p = BME280_OVERSAMPLING_2X;
        dev->settings.osr_t = BME280_OVERSAMPLING_2X;
        dev->settings.filter = BME280_FILTER_COEFF_16;
        dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

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
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);

        print_sensor_data(&comp_data, vSensorBME280DatasStruct);
    }

    return rslt;
}

bool SensorBME280::GetSensorBME280Datas(SensorBME280DatasStruct *vSensorBME280DatasStruct)
{
    struct bme280_dev dev;
    struct identifier id;
    int8_t rslt = BME280_OK;

    if ((id.fd = open(m_I2cBus.c_str(), O_RDWR)) < 0)
    {
        fprintf(stderr, "Failed to open the i2c bus %s\n", argv[1]);
        return false;
    }

    id.dev_addr = BME280_I2C_ADDR_PRIM;
    if (ioctl(id.fd, I2C_SLAVE, id.dev_addr) < 0)
    {
        fprintf(stderr, "Failed to acquire bus access and/or talk to slave.\n");
        return false;
    }

    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;
    dev.intf_ptr = &id;

    if (bme280_init(&dev) != BME280_OK)
    {
        fprintf(stderr, "Failed to initialize the device (code %+d).\n", rslt);
        return false;
    }

    usleep(9000);

    if (getSensorBME280DataNormalMode(&dev) != BME280_OK, &res)
    {
        fprintf(stderr, "Failed to stream sensor data (code %+d).\n", rslt);
        return false;
    }

	return res;
}
#else
bool SensorBME280::GetSensorBME280Datas(SensorBME280DatasStruct* vSensorBME280DatasStruct)
{
    if (vSensorBME280DatasStruct)
    {
        // andom for the moment just for test
        vSensorBME280DatasStruct->epoc = rand() % 100000;
        vSensorBME280DatasStruct->temp = (float)(rand() % 90) - 40.0f;
        vSensorBME280DatasStruct->pres = (float)(rand() % 1000) + 500.0f;
        vSensorBME280DatasStruct->humi = (float)(rand() % 70) + 30.0f;

        return true;
    }

    return false;
}
#endif

std::string SensorBME280::ConvertSensorBME280DatasStructToString(const SensorBME280DatasStruct& vDatas)
{
	int n = snprintf(buffer, BUFFER_LENGTH,
		"{\"epoc\":%u,\"temp\":%.5f,\"pres\":%.5f,\"humi\":%.5f}",
		vDatas.epoc, vDatas.temp, vDatas.pres, vDatas.humi);
	return std::string(buffer, n);
}

std::string SensorBME280::GetSensorBME280DatasToString()
{
    SensorBME280DatasStruct res;
    if (GetSensorBME280Datas(&res))
	    return ConvertSensorBME280DatasStructToString(res);
    return "";
}