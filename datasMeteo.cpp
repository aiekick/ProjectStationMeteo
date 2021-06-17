#include "datasMeteo.h"
#include <qdebug.h>
#include <QtMath>

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
///
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
    return TruncDoubleToPrecision(this->temperatureCelsius, 1);
}
double DatasMeteo::getTemperatureKelvin() const
{
    // https://fr.wikipedia.org/wiki/Kelvin
    return TruncDoubleToPrecision(this->temperatureCelsius + 273.15, 1);
}

double DatasMeteo::getTemperatureFahrenheit() const
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    return TruncDoubleToPrecision(this->temperatureCelsius * 9.0 / 5.0 + 32.0, 1);
}

int DatasMeteo::getHumidity() const
{
    return this->humidity;
}
int DatasMeteo::getPressure() const
{
    return this->pressure;
}

QString DatasMeteo::displayCorrectUnit()
{
    QString temperature;
    if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_CELSIUS)
    {
        temperature = QString::number(getTemperatureCelsius()) + QString::fromUtf8(" °C");
    }
    else if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_FAHRENHEIT)
    {
        temperature = QString::number(getTemperatureFahrenheit()) + " °F";
    }
    else
    {
        temperature = QString::number(getTemperatureKelvin()) + " K";
    }
    return temperature;
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
    this->temperatureCelsius = TruncDoubleToPrecision(vTemperature, 1);
}

void DatasMeteo::setTemperatureKelvin(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Kelvin
    this->temperatureCelsius = TruncDoubleToPrecision(vTemperature - 273.15, 1);
}

void DatasMeteo::setTemperatureFahrenheit(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    this->temperatureCelsius = TruncDoubleToPrecision((vTemperature - 32.0) * 5.0 / 9.0, 1);
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

////////////////////////////////////////////////////
/// PRIVATE
////////////////////////////////////////////////////

double DatasMeteo::TruncDoubleToPrecision(const double vValue, int vPrecision) const
{
    const double po = qPow(10, vPrecision);
    return qFloor(vValue * po) / po;
}
