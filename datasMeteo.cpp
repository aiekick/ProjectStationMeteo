#include "datasMeteo.hpp"

DatasMeteo::DatasMeteo()
{
}

DatasMeteo::DatasMeteo(string v_Picto, float v_Temperature, float v_Humidity, float v_Pressure)
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

float DatasMeteo::getTemperature()
{
	return this->temperature;
}

void DatasMeteo::setTemperature(float v_Temperature)
{
	this->temperature = v_Temperature;
}

float DatasMeteo::getHumidity()
{
	return this->humidity;
}

void DatasMeteo::setHumidity(float v_Humidity)
{
	this->humidity = v_Humidity;
}

float DatasMeteo::getPressure()
{
	return this->pressure;
}

void DatasMeteo::setPressure(float v_Pressure)
{
	this->pressure = v_Pressure;
}