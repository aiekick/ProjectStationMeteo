#ifndef INFOCLIENT_HPP
#define INFOCLIENT_HPP
#include <iostream>
using namespace std;

class Balise
{
private :
	int resolution;
	int temperatureUnit;
	string hourFormat;
	string fontFamily;
	string displayStyle;
	string language;

public :
	Balise();
    Balise(int, int, string, string, string, string);
    ~Balise();
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
