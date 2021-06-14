#ifndef BALISEVILLE_HPP
#define BALISEVILLE_HPP
#include "infosClient.hpp"
#include "datasMeteo.hpp"

class BaliseVille : public InfoClient
{
private:
	DatasMeteo datas;




public:
	BaliseVille(int, int, string, string, string, string, DatasMeteo);
	~BaliseVille();

	string getDatas_Picto();
	double getDatas_Temperature();
	int getDatas_Humidity();
	int getDatas_Pressure();

	void setDatas(DatasMeteo);





};




#endif