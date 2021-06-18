#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP

#include "balise.h"
#include "datasMeteo.h"
#include <QPixmap>
#include <QString>

class BaliseVille : public Balise
{
private:
    DatasMeteo datas;
    DatasMeteo datas2;
    DatasMeteo datas3;
    DatasMeteo datas4;
    DatasMeteo datas5;

public:
    BaliseVille();
    ~BaliseVille();
    QString getDatas_date();
    QString getDatas_Description();
    double getDatas_Temperature();
    int getDatas_Humidity();
    int getDatas_Pressure();
    void RecuperationApi();
    DatasMeteo recupimage(DatasMeteo);

    void setDatas(DatasMeteo);
    DatasMeteo &getDatas();

    DatasMeteo &getDatas2();
    DatasMeteo &getDatas3();
    DatasMeteo &getDatas4();
    DatasMeteo &getDatas5();

private:
    QUrl getWeatherDayUrl();
    QUrl getForeCastDayUrl();
};

#endif
