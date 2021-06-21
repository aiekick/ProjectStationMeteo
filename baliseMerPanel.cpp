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

    ui->customGraphTemperature->SetPadding(40,15,10,20);
    //ui->customGraphTemperature->SetXAxis(11, false, true, 0, 12);
    ui->customGraphTemperature->SetYAxis(1, true, true, 1);
    ui->customGraphTemperature->SetDrawRect(false);

    ui->customGraphHumidity->SetPadding(40,10,10,20);
    ui->customGraphHumidity->SetYAxis(1, true, true, 1);
    ui->customGraphHumidity->SetDrawRect(false);

    ui->customGraphPressure->SetPadding(40,10,10,20);
    ui->customGraphPressure->SetYAxis(1, true, true, 1);
    ui->customGraphPressure->SetDrawRect(false);

    ApplyStyle();
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

    QString pressure = QString::number(baliseMer.getDatas().getPressure());
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    QString meanTemperature = baliseMer.getSummary().getTemperatureToStringFromSettings();

    // on fait ca dans applystyle maintenant vu qu'on doit mettre l'icone en fonction du style
    //this->ui->labelIcon->setPixmap(baliseMer.displayWeatherIcon());

    /////////////////////////////////////////////////////////////////////
    const auto history = baliseMer.getHistory();
    QVector<double> serieTemp;
    QVector<double> seriePres;
    QVector<double> serieHumi;
    for(size_t i = 0; i < history->size(); i++)
    {
        const auto& dm = history->at((int)i);
        serieTemp.push_back(dm.getTemperatureCelsius());
        seriePres.push_back(dm.getPressure());
        serieHumi.push_back(dm.getHumidity());
    }
    ui->customGraphTemperature->SetSerie(serieTemp);
    ui->customGraphTemperature->SetSerieName(QObject::tr("Temperature moyenne des 12 dernieres heures : ") + meanTemperature);
    ui->customGraphPressure->SetSerie(seriePres);
    ui->customGraphPressure->SetSerieName(QObject::tr("Pression ") + pressure + " hPa");
    ui->customGraphHumidity->SetSerie(serieHumi);
    ui->customGraphHumidity->SetSerieName(QObject::tr("Humidité ") + humidity + " %");

    ApplyStyle();
}

void BaliseMerPanel::on_pushButton_See_Graph_Details_clicked()
{
    QChartView* view = baliseMer.displayDetailedChart();
    view->show();
}

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

void BaliseMerPanel::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {
        // vert
        ui->customGraphTemperature->SetSerieCurveStyle(QColor(50,200,50), 5.0);
        ui->customGraphTemperature->SetVerticalGradient(QColor(0,150,0,100), QColor(0,150,0,10));
        ui->customGraphTemperature->SetBackgroundColor(QColor(239,239,239,255));
        ui->customGraphTemperature->SetLinesColor(QColor(30,47,67,255));
        ui->customGraphTemperature->SetValuesColor(QColor(30,47,67,255));
        ui->customGraphTemperature->SetSerieNameStyle(QFont("Arial", 10), QColor(30,47,67,255));

        // orange
        ui->customGraphPressure->SetSerieCurveStyle(QColor(250,150,50), 5.0);
        ui->customGraphPressure->SetVerticalGradient(QColor(200,100,0,100), QColor(200,100,0,10));
        ui->customGraphPressure->SetBackgroundColor(QColor(239,239,239,255));
        ui->customGraphPressure->SetLinesColor(QColor(30,47,67,255));
        ui->customGraphPressure->SetValuesColor(QColor(30,47,67,255));
        ui->customGraphPressure->SetSerieNameStyle(QFont("Arial", 10), QColor(30,47,67,255));

        // bleu
        ui->customGraphHumidity->SetSerieCurveStyle(QColor(50,50,200), 5.0);
        ui->customGraphHumidity->SetVerticalGradient(QColor(0,0,150,100), QColor(0,0,150,10));
        ui->customGraphHumidity->SetBackgroundColor(QColor(239,239,239,255));
        ui->customGraphHumidity->SetLinesColor(QColor(30,47,67,255));
        ui->customGraphHumidity->SetValuesColor(QColor(30,47,67,255));
        ui->customGraphHumidity->SetSerieNameStyle(QFont("Arial", 10), QColor(30,47,67,255));
    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {
        // vert
        ui->customGraphTemperature->SetSerieCurveStyle(QColor(50,200,50), 5.0);
        ui->customGraphTemperature->SetVerticalGradient(QColor(0,150,0,150), QColor(0,150,0,50));
        ui->customGraphTemperature->SetBackgroundColor(QColor(30,47,67,255));
        ui->customGraphTemperature->SetLinesColor(QColor(125,180,218,255));
        ui->customGraphTemperature->SetValuesColor(QColor(125,180,218,255));
        ui->customGraphTemperature->SetSerieNameStyle(QFont("Arial", 10), QColor(125,180,218,255));

        // orange
        ui->customGraphPressure->SetSerieCurveStyle(QColor(250,150,50), 5.0);
        ui->customGraphPressure->SetVerticalGradient(QColor(200,100,0,150), QColor(200,100,0,50));
        ui->customGraphPressure->SetBackgroundColor(QColor(30,47,67,255));
        ui->customGraphPressure->SetLinesColor(QColor(125,180,218,255));
        ui->customGraphPressure->SetValuesColor(QColor(125,180,218,255));
        ui->customGraphPressure->SetSerieNameStyle(QFont("Arial", 10), QColor(125,180,218,255));

        // bleu
        ui->customGraphHumidity->SetSerieCurveStyle(QColor(00,100,250), 5.0);
        ui->customGraphHumidity->SetVerticalGradient(QColor(0,50,200,150), QColor(0,50,200,50));
        ui->customGraphHumidity->SetBackgroundColor(QColor(30,47,67,255));
        ui->customGraphHumidity->SetLinesColor(QColor(125,180,218,255));
        ui->customGraphHumidity->SetValuesColor(QColor(125,180,218,255));
        ui->customGraphHumidity->SetSerieNameStyle(QFont("Arial", 10), QColor(125,180,218,255));
    }

    ui->customGraphTemperature->update();
    ui->customGraphPressure->update();
    ui->customGraphHumidity->update();

    this->ui->labelIcon->setPixmap(baliseMer.displayWeatherIcon());
}


