#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>

#define BME280_I2C_BUS		"/dev/i2c-1"
#define BME280_I2C_ADDR		0x76

// author : Stephane Cuillerdier (Akka technologie) 
// Creation date : 9/06/21
// this program will retrieve infos from the i2cSensor BME280
// infos : Chip ID, Chip Version, Temperature, Pressure, Humidity

// this is based on the script BME280.py delivered to us by AJC for the project

#Official datasheet available from :
#https://www.bosch-sensortec.com/bst/products/all_products/bme280

#define BME280_REG_ID			0xD0

// retrieve Sensor infos (Id, Version, must be passed in params) 
int getSensorID(int vFD, int* vSensorID)
{
	// get chip id
	if (vSensorID)
	{
		*vSensorID = i2c_smbus_read_byte_data(vFD, BME280_ID);
		if (*vSensorID < 0) 
		{
			perror("Read ID");
			return 1;
		}
	}
	
	return 0;
}

#define BME280_REG_DATA			0xF7
#define BME280_REG_CONTROL		0xF4
#define BME280_REG_CONFIG		0xF5

#define BME280_REG_CONTROL_HUM	0xF2
#define BME280_REG_HUM_MSB		0xFD
#define BME280_REG_HUM_LSB		0xFE

#define BME280_OVERSAMPLE_TEMP	2
#define BME280_OVERSAMPLE_PRES	2
#define BME280_OVERSAMPLE_HUM	2
#define BME280_MODE				1

typedef struct { // 0x88
    uint16_t    dig_T1; // 0x88 - 0x89
    int16_t     dig_T2; // 0x8A - 0x8B
    int16_t     dig_T3; // 0x8C - 0x8D
    uint16_t    dig_P1; // 0x8E - 0x8F
    int16_t     dig_P2; // 0x90 - 0x91
    int16_t     dig_P3; // 0x92 - 0x93
    int16_t     dig_P4; // 0x94 - 0x95
    int16_t     dig_P5; // 0x96 - 0x97
    int16_t     dig_P6; // 0x98 - 0x99
    int16_t     dig_P7; // 0x9A - 0x9B
    int16_t     dig_P8; // 0x9C - 0x9D
    int16_t     dig_P9; // 0x9E - 0x9F
	uint8_t		n_A0;	// 0xA0
	uint8_t     dig_H1; // 0xA1
} CALIB_1_Struct;

typedef struct { // 0xE1
    int16_t     dig_H2; // 0xE1 - 0xE2
    uint8_t     dig_H3; // 0xE3
    int16_t     dig_H4; // 0xE4 - 0xE5[3:0]
    int16_t     dig_H5; // 0xE5[7:4] - 0xE6
	uint8_t		dig_H6;	// 0xE7
} CALIB_2_Struct;

static CALIB_1_Struct sCalib1;
static CALIB_2_Struct sCalib2;

// retrieve chip infos (Temperature, Pressure, Humidity, must be passed in params) 
int getSensorDatas(int vFD, int* vSensorTemperature, int* vSensorPressure, int* vSensorHumidity)
{
	// datasheet page 14
	// - Sleep mode: no operation, all registers accessible, lowest power, selected after startup 
	// - Forced mode: perform one measurement, store results and return to sleep mode 
	
	// so we must active the force mode
	
	// Oversample setting for humidity
	i2c_smbus_write_byte_data(vFD, BME280_REG_CONTROL_HUM, BME280_OVERSAMPLE_HUM);
	
	// so we must active the force mode
	int control = (BME280_OVERSAMPLE_TEMP<<5) | (BME280_OVERSAMPLE_PRES<<2) | BME280_MODE;
	i2c_smbus_write_byte_data(vFD, BME280_REG_CONTROL, control);

	//Trimming parameter readout - Page 24 of the datasheet
	
	i2c_smbus_read_block_data(vFD, 0x88, sCalib1);
	i2c_smbus_read_block_data(vFD, 0xE1, sCalib2)
	i2c_smbus_read_block_data(vFD, 0xE4, sCalib3)

	dig_T1 = getUShort(cal1, 0)
	dig_T2 = getShort(cal1, 2)
	dig_T3 = getShort(cal1, 4)

  dig_P1 = getUShort(cal1, 6)
  dig_P2 = getShort(cal1, 8)
  dig_P3 = getShort(cal1, 10)
  dig_P4 = getShort(cal1, 12)
  dig_P5 = getShort(cal1, 14)
  dig_P6 = getShort(cal1, 16)
  dig_P7 = getShort(cal1, 18)
  dig_P8 = getShort(cal1, 20)
  dig_P9 = getShort(cal1, 22)

  dig_H1 = getUChar(cal2, 0)
  dig_H2 = getShort(cal3, 0)
  dig_H3 = getUChar(cal3, 2)

  dig_H4 = getChar(cal3, 3)
  dig_H4 = (dig_H4 << 24) >> 20
  dig_H4 = dig_H4 | (getChar(cal3, 4) & 0x0F)

  dig_H5 = getChar(cal3, 5)
  dig_H5 = (dig_H5 << 24) >> 20
  dig_H5 = dig_H5 | (getUChar(cal3, 4) >> 4 & 0x0F)

  dig_H6 = getChar(cal3, 6)

  # Wait in ms (Datasheet Appendix B: Measurement time and current calculation)
  wait_time = 1.25 + (2.3 * OVERSAMPLE_TEMP) + ((2.3 * OVERSAMPLE_PRES) + 0.575) + ((2.3 * OVERSAMPLE_HUM)+0.575)
  time.sleep(wait_time/1000)  # Wait the required time  

  # Read temperature/pressure/humidity
  data = bus.read_i2c_block_data(addr, REG_DATA, 8)
  pres_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4)
  temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4)
  hum_raw = (data[6] << 8) | data[7]

  #Refine temperature
  var1 = ((((temp_raw>>3)-(dig_T1<<1)))*(dig_T2)) >> 11
  var2 = (((((temp_raw>>4) - (dig_T1)) * ((temp_raw>>4) - (dig_T1))) >> 12) * (dig_T3)) >> 14
  t_fine = var1+var2
  temperature = float(((t_fine * 5) + 128) >> 8);

  # Refine pressure and adjust for temperature
  var1 = t_fine / 2.0 - 64000.0
  var2 = var1 * var1 * dig_P6 / 32768.0
  var2 = var2 + var1 * dig_P5 * 2.0
  var2 = var2 / 4.0 + dig_P4 * 65536.0
  var1 = (dig_P3 * var1 * var1 / 524288.0 + dig_P2 * var1) / 524288.0
  var1 = (1.0 + var1 / 32768.0) * dig_P1
  if var1 == 0:
    pressure=0
  else:
    pressure = 1048576.0 - pres_raw
    pressure = ((pressure - var2 / 4096.0) * 6250.0) / var1
    var1 = dig_P9 * pressure * pressure / 2147483648.0
    var2 = pressure * dig_P8 / 32768.0
    pressure = pressure + (var1 + var2 + dig_P7) / 16.0

  # Refine humidity
  humidity = t_fine - 76800.0
  humidity = (hum_raw - (dig_H4 * 64.0 + dig_H5 / 16384.0 * humidity)) * (dig_H2 / 65536.0 * (1.0 + dig_H6 / 67108864.0 * humidity * (1.0 + dig_H3 / 67108864.0 * humidity)))
  humidity = humidity * (1.0 - dig_H1 * humidity / 524288.0)
  if humidity > 100:
    humidity = 100
  elif humidity < 0:
    humidity = 0

  return temperature/100.0,pressure/100.0,humidity
  
	return 0;
}

int main(int argc, char * argv[])
{
	// open i2c device
	int fd = open(BME280_I2C_BUS, O_RDWR);
	if (fd < 0) 
	{
		perror(BME280_I2C_BUS);
		exit(EXIT_FAILURE);
	}

	// fix slave addr for communication
	if (ioctl(fd, I2C_SLAVE, BME280_I2C_ADDR) < 0) 
	{
		perror("Slave unreachable");
		exit(EXIT_FAILURE);
	}
	
	int chipID;
	if (getChipID(fd, &chipID))
	{
		exit(EXIT_FAILURE);
	}
	
	printf("Chip ID       : %d\n", chip_id);
	printf("Temperature   : %d\n C", temperature);
	printf("Pressure      : %d\n hPa", pressure);
	printf("Humidity      : %d\n %", humidity);
	
	return EXIT_SUCCESS;
}