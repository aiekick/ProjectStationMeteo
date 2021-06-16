#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP

#include "balise.h"
#include "datasMeteo.h"

#include <QString>

class BaliseVille : public Balise
{
private:
    DatasMeteo datas;

public:
    BaliseVille();
    BaliseVille(int, int, string, string, string, string, DatasMeteo);
    ~BaliseVille();

    QString getDatas_Picto();
    double getDatas_Temperature();
    int getDatas_Humidity();
    int getDatas_Pressure();
    void RecuperationApi();
    void setDatas(DatasMeteo);
    DatasMeteo &getDatas() ;
};

#endif
