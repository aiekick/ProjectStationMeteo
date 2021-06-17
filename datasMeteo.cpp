#include "datasMeteo.h"
#include <qdebug.h>

////////////////////////////////////////////////////
/// CTOR / DTOR
////////////////////////////////////////////////////

DatasMeteo::DatasMeteo()
{

}

DatasMeteo::DatasMeteo(QString v_Picto, double v_Temperature, double v_Humidity, double v_Pressure)
{
	setPicto(v_Picto);
    setTemperatureCelsius(v_Temperature);
	setHumidity(v_Humidity);
	setPressure(v_Pressure);
}

DatasMeteo::~DatasMeteo()
{

}

////////////////////////////////////////////////////
/// GETTERS
////////////////////////////////////////////////////
QString DatasMeteo::getDate() const
{
    return this-> date;

}
QString DatasMeteo::getPicto() const
{
    return this->picto;
}
double DatasMeteo::getTemperatureCelsius() const
{
    double tempFormated = this->temperatureCelsius * 10;
    tempFormated = (int)tempFormated;
    tempFormated = tempFormated / 10;
    return tempFormated;
}
double DatasMeteo::getTemperatureKelvin() const
{
    // https://fr.wikipedia.org/wiki/Kelvin
    return this->temperatureCelsius + 273.15;
}

double DatasMeteo::getTemperatureFahrenheit() const
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    return this->temperatureCelsius * 9.0 / 5.0 + 32.0;
}

int DatasMeteo::getHumidity() const
{
    return this->humidity;
}
int DatasMeteo::getPressure() const
{
    return this->pressure;
}

QString DatasMeteo::getVille() const
{
    return ville;
}

////////////////////////////////////////////////////
/// SETTERS
////////////////////////////////////////////////////
void DatasMeteo::setDate(const QString &vdate)
{

  this->date=vdate;
}

void DatasMeteo::setPicto(const QString& vPicto)
{
    this->picto = vPicto;
}

void DatasMeteo::setTemperatureCelsius(const double& vTemperature)
{
    double tempFormated = vTemperature * 10;
    tempFormated = (int)tempFormated;
    tempFormated = tempFormated / 10;
    this->temperatureCelsius = tempFormated;
}

void DatasMeteo::setTemperatureKelvin(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Kelvin
    this->temperatureCelsius = vTemperature - 273.15;
}

void DatasMeteo::setTemperatureFahrenheit(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    this->temperatureCelsius = (vTemperature - 32.0) * 5.0 / 9.0;
}

void DatasMeteo::setHumidity(const int& vHumidity)
{
    this->humidity = vHumidity;
}

void DatasMeteo::setPressure(const int& vPressure)
{
    this->pressure = vPressure;
}

void DatasMeteo::setVille(const QString& vNewVille)
{
    this->ville = vNewVille;
}