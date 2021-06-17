#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <QString>

class DatasMeteo
{
private :
    QString picto;                      // icone pour les données
    QString ville;                      // la ville associée aux donnée tempérées
    double temperatureCelsius = 0.0;    // temperature en celsius
    double humidity = 0.0;              // humitidty en %
    double pressure = 0.0;              // pressure en hPa
    QString date;
    QString icon;




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
    double getHumidity() const;
    double getPressure() const;

    void setDate(const QString& vdate);
    void setPicto(const QString& vPicto);
    void setVille(const QString& vNewVille);
    void setTemperatureCelsius(const double& vTemperature);
    void setTemperatureKelvin(const double& vTemperature);
    void setTemperatureFahrenheit(const double& vTemperature);
    void setHumidity(const double& vHumidity);
    void setPressure(const double& vPressure);
    const QString &getIcon() const;
    void setIcon(const QString &newIcon);
};

#endif
