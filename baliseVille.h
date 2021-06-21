#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP

#include "balise.h"
#include "datasMeteo.h"
#include <QPixmap>
#include <QString>

class BaliseVille : public Balise
{
private:
    DatasMeteo datasJourActu;
    DatasMeteo datasForeCast1;
    DatasMeteo datasForeCast2;
    DatasMeteo datasForeCast3;
    DatasMeteo datasForeCast4;
    DatasMeteo datasForeCast5;

public:
    BaliseVille();
    ~BaliseVille();
    QString getDatas_date();
    QString getDatas_Description();
    double getDatas_Temperature();
    int getDatas_Humidity();
    int getDatas_Pressure();
    void Recuperation_Api_Current();
    void Recuperation_Api_ForeCast();
    DatasMeteo recupimage(DatasMeteo);

    void setDatasJourActu(DatasMeteo);
    DatasMeteo &getDatasJourActu();
    DatasMeteo &getDatasForeCast1();
    DatasMeteo &getDatasForeCast2();
    DatasMeteo &getDatasForeCast3();
    DatasMeteo &getDatasForeCast4();
    DatasMeteo &getDatasForeCast5();

private:
    QUrl getWeatherDayUrl();
    QUrl getForeCastDayUrl();
};

#endif
