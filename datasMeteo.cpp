#include "datasMeteo.h"

DatasMeteo::DatasMeteo()
{
	setTemperature(1);
	setHumidity(1);
	setPressure(1);
}

DatasMeteo::DatasMeteo(string v_Picto, double v_Temperature, double v_Humidity, double v_Pressure)
{
	setPicto(v_Picto);
	setTemperature(v_Temperature);
	setHumidity(v_Humidity);
	setPressure(v_Pressure);
}

DatasMeteo::~DatasMeteo()
{
}

string DatasMeteo::getPicto()
{
	return this->picto;
}

void DatasMeteo::setPicto(string v_Picto)
{
	this->picto = v_Picto;
}

double DatasMeteo::getTemperature()
{
	return this->temperature;
}

void DatasMeteo::setTemperature(double v_Temperature)
{
	this->temperature = v_Temperature;
}

double DatasMeteo::getHumidity()
{
	return this->humidity;
}

void DatasMeteo::setHumidity(double v_Humidity)
{
	this->humidity = v_Humidity;
}

double DatasMeteo::getPressure()
{
	return this->pressure;
}

void DatasMeteo::setPressure(double v_Pressure)
{
	this->pressure = v_Pressure;
}

double DatasMeteo::kelvinToCelsius()
{
	this->temperature -= 273.15;
	return this->temperature;
}

double DatasMeteo::celsiusToFahrenheit()
{
	this->temperature += 32;
	return this->temperature;
}

double DatasMeteo::fahrenheitToCelsius()
{
	this->temperature -= 32;
	return this->temperature;
}