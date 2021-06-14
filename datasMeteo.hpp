#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <iostream>
using namespace std;

class DatasMeteo
{
private :
	string picto;
	float temperature;
	float humidity;
	float pressure;

public:
	DatasMeteo();
	DatasMeteo(string, float, float, float);
	~DatasMeteo();
	string getPicto();
	void setPicto(string);
	float getTemperature();
	void setTemperature(float);
	float getHumidity();
	void setHumidity(float);
	float getPressure();
	void setPressure(float);

};

#endif