#include "baliseVille.h"

BaliseVille::BaliseVille(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language, DatasMeteo v_DatasMeteo)
:Balise(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
	setDatas(v_DatasMeteo);
}

BaliseVille::~BaliseVille()
{
}

string BaliseVille::getDatas_Picto()
{
	return this->datas.getPicto();
}

double BaliseVille::getDatas_Temperature()
{
	return this->datas.getTemperature();
}

int BaliseVille::getDatas_Humidity()
{
	return this->datas.getHumidity();
}

int BaliseVille::getDatas_Pressure()
{
	return this->datas.getPressure();
}

void BaliseVille::setDatas(DatasMeteo v_DatasMeteo)
{
	this->datas.setPicto(v_DatasMeteo.getPicto());
	this->datas.setTemperature(v_DatasMeteo.getTemperature());
	this->datas.setHumidity(v_DatasMeteo.getHumidity());
	this->datas.setPressure(v_DatasMeteo.getPressure());
}
