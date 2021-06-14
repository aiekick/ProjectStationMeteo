#include "balise.h"

Balise::Balise(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language)
{
	setResolution(v_resolution);
	setTemperatureUnit(v_temperatureUnit);
	setHourFormat(v_hourFormat);
	setFontFamily(v_fontFamily);
	setDisplayStyle(v_displayStyle);
	setLanguage(v_language);
}

Balise::~Balise()
{

}

int Balise::getResolution()
{
	return this->resolution;
}

void Balise::setResolution(int v_resolution)
{
	this->resolution = v_resolution;
}

int Balise::getTemperatureUnit()
{
	return this->temperatureUnit;
}

void Balise::setTemperatureUnit(int v_temperatureUnit)
{
	this->temperatureUnit = v_temperatureUnit;
}

string Balise::getHourFormat()
{
	return this->hourFormat;
}

void Balise::setHourFormat(string v_hourFormat)
{
	this->hourFormat = v_hourFormat;
}

string Balise::getFontFamily()
{
	return this->fontFamily;
}

void Balise::setFontFamily(string v_fontFamily)
{
	this->fontFamily = v_fontFamily;
}

string Balise::getDisplayStyle()
{
	return this->displayStyle;
}

void Balise::setDisplayStyle(string v_displayStyle)
{
	this->displayStyle = v_displayStyle;
}

string Balise::getLanguage()
{
	return this->language;
}

void Balise::setLanguage(string v_language)
{
	this->language = v_language;
}
