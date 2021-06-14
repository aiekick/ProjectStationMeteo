#ifndef INFOCLIENT_HPP
#define INFOCLIENT_HPP
#include <iostream>
using namespace std;

class InfoClient
{
private :
	int resolution;
	int temperatureUnit;
	string hourFormat;
	string fontFamily;
	string displayStyle;
	string language;

public :
	InfoClient(int, int, string, string, string, string);
	~InfoClient();
	int getResolution();
	void setResolution(int);
	int getTemperatureUnit();
	void setTemperatureUnit(int);
	string getHourFormat();
	void setHourFormat(string);
	string getFontFamily();
	void setFontFamily(string);
	string getDisplayStyle();
	void setDisplayStyle(string);
	string getLanguage();
	void setLanguage(string);

};

#endif