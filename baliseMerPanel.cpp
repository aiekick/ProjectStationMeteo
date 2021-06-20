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

BaliseMerPanel::BaliseMerPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::baliseMerPanel)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    //ui->customGraphTemperature->SetBackgroundColor(QColor(31,48,68));
    ui->customGraphTemperature->SetPadding(40,20,10,10);
    ui->customGraphTemperature->SetLinesColor(QColor(0,0,0));
    ui->customGraphTemperature->SetValuesColor(QColor(0,0,0));
    //ui->customGraphTemperature->SetXAxis(11, true, true, 0, 12);
    ui->customGraphTemperature->SetYAxis(1, true, true, 1);
    ui->customGraphTemperature->SetDrawRect(false);
    ui->customGraphTemperature->SetVerticalGradient(QColor(0,100,0,100), QColor(0,100,0,10));

    //ui->customGraphHumidity->SetBackgroundColor(QColor(31,48,68));
    ui->customGraphHumidity->SetPadding(40,10,10,20);
    ui->customGraphHumidity->SetLinesColor(QColor(0,0,0));
    ui->customGraphHumidity->SetValuesColor(QColor(0,0,0));
    //ui->customGraphTemperature->SetXAxis(11, true, true, 0, 12);
    ui->customGraphHumidity->SetYAxis(1, true, true, 1);
    ui->customGraphHumidity->SetDrawRect(false);
    ui->customGraphHumidity->SetVerticalGradient(QColor(0,100,0,100), QColor(0,100,0,10));

    //ui->customGraphPressure->SetBackgroundColor(QColor(31,48,68));
    ui->customGraphPressure->SetPadding(40,10,10,20);
    ui->customGraphPressure->SetLinesColor(QColor(0,0,0));
    ui->customGraphPressure->SetValuesColor(QColor(0,0,0));
    //ui->customGraphPressure->SetXAxis(11, true, true, 0, 12);
    ui->customGraphPressure->SetYAxis(1, true, true, 1);
    ui->customGraphPressure->SetDrawRect(false);
    ui->customGraphPressure->SetVerticalGradient(QColor(0,100,0,100), QColor(0,100,0,10));
}

BaliseMerPanel::~BaliseMerPanel()
{
    delete ui;
}

void BaliseMerPanel::updateData()
{
    baliseMer.getHistory()->clear();

    baliseMer.requestData();
    baliseMer.requestMeanData();

    // Temperature
    QString temperature = baliseMer.getDatas().getTemperatureToStringFromSettings();
    this->ui->label_Temperature_Mer->setText(temperature);

    QString pressure = QString::number(baliseMer.getDatas().getPressure());
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    QString meanTemperature = baliseMer.getSummary().getTemperatureToStringFromSettings();
    this->ui->label_2->setPixmap(baliseMer.displayWeatherIcon());

    /////////////////////////////////////////////////////////////////////
    const auto history = baliseMer.getHistory();
    QVector<double> serieTemp;
    QVector<double> seriePres;
    QVector<double> serieHumi;
    for(size_t i = 0; i < history->size(); i++)
    {
        const auto& dm = history->at(i);
        serieTemp.push_front(dm.getTemperatureCelsius());
        seriePres.push_front(dm.getPressure());
        serieHumi.push_front(dm.getHumidity());
    }
    ui->customGraphTemperature->SetSerie(serieTemp, QColor(100,150,200), 5.0);
    ui->customGraphTemperature->SetSerieName(QObject::tr("Temperature moyennes des 12 dernieres heures : ") + meanTemperature, QFont("Arial", 10), QColor(100,150,200), Qt::AnchorPoint::AnchorBottom);
    ui->customGraphPressure->SetSerie(seriePres, QColor(200,150,100), 5.0);
    ui->customGraphPressure->SetSerieName(QObject::tr("Pression ") + pressure + " hPa", QFont("Arial", 10), QColor(200,150,100));
    ui->customGraphHumidity->SetSerie(serieHumi, QColor(150,200,150), 5.0);
    ui->customGraphHumidity->SetSerieName(QObject::tr("Humidité ") + humidity + " %", QFont("Arial", 10), QColor(150,200,150));
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

