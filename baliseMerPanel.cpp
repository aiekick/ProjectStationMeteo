#include "baliseMerPanel.h"
#include "ui_baliseMerPanel.h"
#include "balise.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>
#include "GlobalSettings.h"

#include <QtCharts>
#include <QSplineSeries>

//#include <qgridlayout.h>

BaliseMerPanel::BaliseMerPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::baliseMerPanel)
{
	ui->setupUi(this);
}

BaliseMerPanel::~BaliseMerPanel()
{
	delete ui;
}

void BaliseMerPanel::updateData()
{
    baliseMer.requestData();
    baliseMer.requestMeanData();
   
    // Temperature
    QString temperature = baliseMer.getDatas().getTemperatureToStringFromSettings();
    this->ui->label_Temperature_Mer->setText(temperature);

    // Pressure
    QString pressure = QString::number(baliseMer.getDatas().getPressure());
    this->ui->label_Pressure_Mer->setText(pressure + " hPa");

    //Humidity
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    this->ui->label_Humidity_Mer->setText(humidity + " %");

    // Mean Temperature
    QString meanTemperature = baliseMer.getSummary().getTemperatureToStringFromSettings();
    this->ui->label_Mean_Temperature_Mer->setText(meanTemperature);
   
    // Display weather icon depending on the pressure
    this->ui->label_2->setPixmap(baliseMer.displayWeatherIcon());

    // Display detailed chart
    this->ui->gridLayout->addWidget(baliseMer.displayDetailedChart(), 0, 0); // Integrated to the main window

    // Clear history
    //baliseMer.getHistory()->clear(); // A deplacer ailleurs
}

void BaliseMerPanel::on_pushButton_Refresh_clicked()
{
    updateData();
}

void BaliseMerPanel::on_pushButton_See_Graph_Details_clicked()
{
    QChartView* view = baliseMer.displayDetailedChart();
    view->show();
}

