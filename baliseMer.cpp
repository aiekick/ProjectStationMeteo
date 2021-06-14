#include "baliseMer.hpp"
#include <sstream>

BaliseMer::BaliseMer(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language,
DatasMeteo v_Datas, DatasMeteo v_Summary, vector<DatasMeteo> v_History)
:InfoClient(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
	setDatas(v_Datas);
	setSummary(v_Summary);
	setHistory(v_History);
}

BaliseMer::~BaliseMer()
{
}

DatasMeteo BaliseMer::getDatas()
{
	return this->datas;
}

void BaliseMer::setDatas(DatasMeteo v_Datas)
{
	this->datas = v_Datas;
}

DatasMeteo BaliseMer::getSummary()
{
	return this->summary;
}

void BaliseMer::setSummary(DatasMeteo v_Summary)
{
	this->summary = v_Summary;
}

vector<DatasMeteo> BaliseMer::getHistory()
{
	return this->history;
}

void BaliseMer::setHistory(vector<DatasMeteo> v_History)
{
	this->history = v_History;
}

string BaliseMer::displayDatas()
{
	ostringstream(oss);
	oss << "Temperature : " << datas.getTemperature() << endl; 
	oss << "Humidity : " << datas.getHumidity() << endl; 
	oss << "Pressure : " << datas.getPressure() << endl; 

	return oss.str();
}