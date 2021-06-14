#include "infosClient.hpp"

InfoClient::InfoClient(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language)
{
	setResolution(v_resolution);
	setTemperatureUnit(v_temperatureUnit);
	setHourFormat(v_hourFormat);
	setFontFamily(v_fontFamily);
	setDisplayStyle(v_displayStyle);
	setLanguage(v_language);
}

InfoClient::~InfoClient()
{

}

int InfoClient::getResolution()
{
	return this->resolution;
}

void InfoClient::setResolution(int v_resolution)
{
	this->resolution = v_resolution;
}

int InfoClient::getTemperatureUnit()
{
	return this->temperatureUnit;
}

void InfoClient::setTemperatureUnit(int v_temperatureUnit)
{
	this->temperatureUnit = v_temperatureUnit;
}

string InfoClient::getHourFormat()
{
	return this->hourFormat;
}

void InfoClient::setHourFormat(string v_hourFormat)
{
	this->hourFormat = v_hourFormat;
}

string InfoClient::getFontFamily()
{
	return this->fontFamily;
}

void InfoClient::setFontFamily(string v_fontFamily)
{
	this->fontFamily = v_fontFamily;
}

string InfoClient::getDisplayStyle()
{
	return this->displayStyle;
}

void InfoClient::setDisplayStyle(string v_displayStyle)
{
	this->displayStyle = v_displayStyle;
}

string InfoClient::getLanguage()
{
	return this->language;
}

void InfoClient::setLanguage(string v_language)
{
	this->language = v_language;
}