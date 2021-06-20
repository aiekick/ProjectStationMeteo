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
#include <QVector>

//#include <qgridlayout.h>

BaliseMerPanel::BaliseMerPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::baliseMerPanel)
{
	ui->setupUi(this);
    ui->retranslateUi(this);
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
    qDebug() <<"_______________" << pressure;

    //Humidity
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    this->ui->label_Humidity_Mer->setText(humidity + " %");

    // Mean Temperature
    QString meanTemperature = baliseMer.getSummary().getTemperatureToStringFromSettings();
    this->ui->label_Mean_Temperature_Mer->setText(meanTemperature);
   
    // Display weather icon depending on the pressure
    this->ui->label_2->setPixmap(baliseMer.displayWeatherIcon());


    // Clear history
    //baliseMer.getHistory()->clear(); // A deplacer ailleurs



    /////////////////////////////////////////////////////////////////////
    // Humidity chart
    this->ui->verticalLayout_Graph_Humidity->addWidget(baliseMer.humidityChart(), 0, 0);

    // Pressure chart
    this->ui->verticalLayout_Graph_Pressure->addWidget(baliseMer.pressureChart(), 0, 0);

    // Temperature chart
    this->ui->verticalLayout_Graph_Temperature->addWidget(baliseMer.temperatureChart(), 0, 0);


    /*const auto history = baliseMer.getHistory();
    QVector<double> serie;
    for(size_t i = 0; i < history->size(); i++)
    {
        const auto& dm = history->at(i);
        serie.push_back(dm.getTemperatureCelsius());
    }
    this->ui->widgetGraph->SetSerie(serie);*/
}

void BaliseMerPanel::on_pushButton_See_Graph_Details_clicked()
{
    QChartView* view = baliseMer.displayDetailedChart();
    view->show();
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void BaliseMerPanel::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
   }
}

