#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <QString>
#include "GlobalSettings.h"

class DatasMeteo
{
private :
    QString picto;                      // icone pour les données
    QString ville;                      // la ville associée aux donnée tempérées
    double temperatureCelsius = 0.0;    // temperature en celsius
    int humidity = 0;              // humitidty en %
    int pressure = 0;              // pressure en hPa
    QString date;



public:
	DatasMeteo();
    DatasMeteo(QString, double, double, double);
	~DatasMeteo();

    QString getDate()const;
    QString getPicto() const;
    QString getVille() const;
    double getTemperatureCelsius() const;
    double getTemperatureKelvin() const;
    double getTemperatureFahrenheit() const;
    int getHumidity() const;
    int getPressure() const;
    QString displayCorrectUnit();
    

    void setDate(const QString& vdate);
    void setPicto(const QString& vPicto);
    void setVille(const QString& vNewVille);
    void setTemperatureCelsius(const double& vTemperature);
    void setTemperatureKelvin(const double& vTemperature);
    void setTemperatureFahrenheit(const double& vTemperature);
    void setHumidity(const int& vHumidity);
    void setPressure(const int& vPressure);
};

#endif
