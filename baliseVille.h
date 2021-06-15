#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP
#include "balise.h"
#include "datasMeteo.h"

class BaliseVille : public Balise
{
private:
    DatasMeteo datas;


public:
    BaliseVille() :Balise()   {}

    BaliseVille(int, int, string, string, string, string, DatasMeteo);
    ~BaliseVille();

    string getDatas_Picto();
    double getDatas_Temperature();
    int getDatas_Humidity();
    int getDatas_Pressure();
    void RecuperationApi();
    void setDatas(DatasMeteo);




     DatasMeteo &getDatas() ;
};

#endif
