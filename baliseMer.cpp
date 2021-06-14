#include "baliseMer.hpp"
#include <sstream>

BaliseMer::BaliseMer(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language,
DatasMeteo v_Datas, DatasMeteo v_Summary, vector<DatasMeteo> v_History)
:InfoClient(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
}

BaliseMer::~BaliseMer()
{
}

double BaliseMer::getTemperature()
{
    return this->temperature;
}

void BaliseMer::setTemperature(double v_Temperature)
{
    this->temperature = v_Temperature;
}

double BaliseMer::getPressure()
{
    return this->pressure;
}

void BaliseMer::setPressure(double v_Pressure)
{
    this->pressure = v_Pressure;
}

double BaliseMer::getHumidity()
{
    return this->humidity;
}

void BaliseMer::setHumidity(double v_Humidity)
{
    this->humidity = v_Humidity;
}