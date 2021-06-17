#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP

#include "balise.h"
#include "datasMeteo.h"

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
    BaliseVille(int, int, string, string, string, string, DatasMeteo);
    ~BaliseVille();
    QString getDatas_date();
    QString getDatas_Description();
    double getDatas_Temperature();
    int getDatas_Humidity();
    int getDatas_Pressure();
    void RecuperationApi();
    void setDatas(DatasMeteo);
    DatasMeteo &getDatas() ;


};

#endif
