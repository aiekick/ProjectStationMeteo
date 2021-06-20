#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <QPixmap>
#include <QString>
#include "GlobalSettings.h"

class DatasMeteo
{
private :
    QString ville;                      // la ville associée aux donnée tempérées
    double temperatureCelsius = 0.0;    // temperature en celsius
    int humidity = 0;                   // humitidty en %
    int pressure = 0;                   // pressure en hPa
    QString date;                       // date de la mesure
    QString description;                // description du temps
    QString icon;                       // icone pour les données
    QPixmap imagetemp;

public:
	DatasMeteo();
    DatasMeteo(QString, double, double, double);
	~DatasMeteo();


    QPixmap getImage()const;
    QString getDate()const;
    QString getDescription() const;
    QString getVille() const;
    double getTemperatureCelsius() const;
    double getTemperatureKelvin() const;
    double getTemperatureFahrenheit() const;
    int getHumidity() const;
    int getPressure() const;
    const QString &getIcon() const;

    QString getTemperatureToStringFromSettings();
    void setImage(const QPixmap& vimage);
    void setDate(const QString& vdate);
    void setDescription(const QString& vPicto);
    void setVille(const QString& vNewVille);
    void setTemperatureCelsius(const double& vTemperature);
    void setTemperatureKelvin(const double& vTemperature);
    void setTemperatureFahrenheit(const double& vTemperature);
    void setHumidity(const int& vHumidity);
    void setPressure(const int& vPressure);
    void setIcon(const QString &newIcon);

private:
    double TruncDoubleToPrecision(const double vValue, int vPrecision) const;
};

#endif
