#ifndef BALISEMER_HPP
#define BALISEMER_HPP
#include "infosClient.hpp"
#include "datasMeteo.hpp"
#include <vector>

class BaliseMer : public InfoClient
{
private:
	double temperature;
	double humidity;
	double pressure;
	DatasMeteo datas;
	DatasMeteo summary;
	vector<DatasMeteo> history;

public:
	
	BaliseMer(int, int, string, string, string, string, DatasMeteo, DatasMeteo, vector<DatasMeteo>);
	~BaliseMer();

	double getTemperature();
	void setTemperature(double);
	double getPressure();
	void setPressure(double);
	double getHumidity();
	void setHumidity(double);

};

#endif