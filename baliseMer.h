#ifndef BALISEMER_HPP
#define BALISEMER_HPP
#include "balise.h"
#include "datasMeteo.h"
#include <vector>

class BaliseMer : public Balise
{
private:
	DatasMeteo datas;
	DatasMeteo summary;
	vector<DatasMeteo> history;
	double meanTemp = 0.0;               // Temperature moyenne

public:
	BaliseMer();
	BaliseMer(int, int, string, string, string, string, DatasMeteo, DatasMeteo, vector<DatasMeteo>);
	~BaliseMer();

	DatasMeteo getDatas();
	vector<DatasMeteo>* getHistory();
	double getMeanTemp();


	void requestData();     // Send request to server and retrieve infos
	void requestMeanData(); // Same as requestData but only for temperature over the last 12 hours
	void setMeanTemp(double);
};

#endif