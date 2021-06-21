#include "datasMeteo.h"
#include <qdebug.h>
#include <QtMath>

const int TRUNC_PRECISION = 1;

////////////////////////////////////////////////////
/// CTOR / DTOR
////////////////////////////////////////////////////

DatasMeteo::DatasMeteo() = default;
DatasMeteo::~DatasMeteo() = default;

////////////////////////////////////////////////////
/// GETTERS
////////////////////////////////////////////////////

const QString &DatasMeteo::getIcon() const
{
    return icon;
}

QPixmap DatasMeteo::getImage() const
{
    return this->imagetemp;
}

QString DatasMeteo::getDate() const
{
    return this-> date;

}

QString DatasMeteo::getDescription() const
{
    return this->description;
}

double DatasMeteo::getTemperatureCelsius() const
{
    return TruncDoubleToPrecision(this->temperatureCelsius, TRUNC_PRECISION);
}

double DatasMeteo::getTemperatureKelvin() const
{
    // https://fr.wikipedia.org/wiki/Kelvin
    return TruncDoubleToPrecision(this->temperatureCelsius + 273.15, TRUNC_PRECISION);
}

double DatasMeteo::getTemperatureFahrenheit() const
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    return TruncDoubleToPrecision(this->temperatureCelsius * 9.0 / 5.0 + 32.0, TRUNC_PRECISION);
}

double DatasMeteo::getTemperatureMinCelsius() const
{
    return TruncDoubleToPrecision(this->temperatureMinCelsius, TRUNC_PRECISION);
}

double DatasMeteo::getTemperatureMinKelvin() const
{
    // https://fr.wikipedia.org/wiki/Kelvin
    return TruncDoubleToPrecision(this->temperatureMinCelsius + 273.15, TRUNC_PRECISION);
}

double DatasMeteo::getTemperatureMinFahrenheit() const
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    return TruncDoubleToPrecision(this->temperatureMinCelsius * 9.0 / 5.0 + 32.0, TRUNC_PRECISION);
}

double DatasMeteo::getHumidity() const
{
    return this->humidity;
}

double DatasMeteo::getPressure() const
{
    return this->pressure;
}

QString DatasMeteo::getTemperatureToStringFromSettings()
{
    switch (GlobalSettings::Instance()->getTemperatureUnit())
    {
    case TemperatureUnitEnum::UNIT_CELSIUS:
        return QString::number(getTemperatureCelsius()) + QString::fromUtf8(u8"\u00B0""C");
    case TemperatureUnitEnum::UNIT_FAHRENHEIT:
        return QString::number(getTemperatureFahrenheit()) + QString::fromUtf8(u8"\u00B0""F");
    case TemperatureUnitEnum::UNIT_KELVIN:
        return QString::number(getTemperatureKelvin()) + QString::fromUtf8(" K");
    }

    return "";
}


QString DatasMeteo::getTemperatureMinToStringFromSettings()
{
    switch (GlobalSettings::Instance()->getTemperatureUnit())
    {
    case TemperatureUnitEnum::UNIT_CELSIUS:
        return QString::number(getTemperatureMinCelsius()) + QString::fromUtf8(u8"\u00B0""C");
    case TemperatureUnitEnum::UNIT_FAHRENHEIT:
        return QString::number(getTemperatureMinFahrenheit()) + QString::fromUtf8(u8"\u00B0""F");
    case TemperatureUnitEnum::UNIT_KELVIN:
        return QString::number(getTemperatureMinKelvin()) + QString::fromUtf8(" K");
    }

    return "";
}


QString DatasMeteo::getVille() const
{
    return ville;
}

////////////////////////////////////////////////////
/// SETTERS
////////////////////////////////////////////////////

void DatasMeteo::setImage(const QPixmap &vimage)
{
    imagetemp = vimage;
}

void DatasMeteo::setIcon(const QString &newIcon)
{
    icon = newIcon;
}

void DatasMeteo::setDate(const QString &vdate)
{

  this->date=vdate;
}

void DatasMeteo::setDescription(const QString& vDescription)
{
    this->description = vDescription;
}

void DatasMeteo::setTemperatureCelsius(const double& vTemperature)
{
    this->temperatureCelsius = TruncDoubleToPrecision(vTemperature, TRUNC_PRECISION);
}

void DatasMeteo::setTemperatureKelvin(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Kelvin
    this->temperatureCelsius = TruncDoubleToPrecision(vTemperature - 273.15, TRUNC_PRECISION);
}

void DatasMeteo::setTemperatureFahrenheit(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    this->temperatureCelsius = TruncDoubleToPrecision((vTemperature - 32.0) * 5.0 / 9.0, TRUNC_PRECISION);

}
void DatasMeteo::setTemperatureMinCelsius(const double& vTemperature)
{
    this->temperatureMinCelsius = TruncDoubleToPrecision(vTemperature, TRUNC_PRECISION);
}

void DatasMeteo::setTemperatureMinKelvin(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Kelvin
    this->temperatureMinCelsius = TruncDoubleToPrecision(vTemperature - 273.15, TRUNC_PRECISION);
}

void DatasMeteo::setTemperatureMinFahrenheit(const double& vTemperature)
{
    // https://fr.wikipedia.org/wiki/Degr%C3%A9_Fahrenheit
    this->temperatureMinCelsius = TruncDoubleToPrecision((vTemperature - 32.0) * 5.0 / 9.0, TRUNC_PRECISION);
}

void DatasMeteo::setHumidity(const double& vHumidity)
{
    this->humidity = TruncDoubleToPrecision(vHumidity, TRUNC_PRECISION);
}

void DatasMeteo::setPressure(const double& vPressure)
{
    this->pressure = TruncDoubleToPrecision(vPressure, TRUNC_PRECISION);
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
