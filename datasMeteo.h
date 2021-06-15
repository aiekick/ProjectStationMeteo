#ifndef DATASMETEO_HPP
#define DATASMETEO_HPP

#include <QString>
#include <iostream>
using namespace std;

class DatasMeteo
{
private :
	string picto;
	float temperature;
	float humidity;
	float pressure;
    QString ville;


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



    const QString &getVille() const;
    void setVille(const QString &newVille);
};

#endif
