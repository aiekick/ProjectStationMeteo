#ifndef BALISEMER_HPP
#define BALISEMER_HPP
#include "balise.h"
#include "datasMeteo.h"
#include <vector>
#include <QPixmap>
#include <QtCharts>

class BaliseMer : public Balise
{
private:
	DatasMeteo datas;
	DatasMeteo summary;					// Average values
	vector<DatasMeteo> history;

public:
	BaliseMer();
    ~BaliseMer();

	DatasMeteo getDatas();
	vector<DatasMeteo>* getHistory();
	DatasMeteo getSummary();
	QPixmap displayWeatherIcon();
	QChartView* displayDetailedChart();

	void requestData();     // Send request to server and retrieve infos
	void requestMeanData(); // Same as requestData but only for temperature over the last 12 hours
};

#endif
