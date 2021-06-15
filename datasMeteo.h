#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <iostream>
using namespace std;

class DatasMeteo
{
private :
	string picto;
	double temperature;
	double humidity;
	double pressure;

public:
	DatasMeteo();
	DatasMeteo(string, double, double, double);
	~DatasMeteo();
	string getPicto();
	void setPicto(string);
	double getTemperature();
	void setTemperature(double);
	double getHumidity();
	void setHumidity(double);
	double getPressure();
	void setPressure(double);

	double kelvinToCelsius();
	double celsiusToFahrenheit();
	double fahrenheitToCelsius();

};

#endif