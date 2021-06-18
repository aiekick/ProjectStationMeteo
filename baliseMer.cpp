#include "baliseMer.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>
#include <qapplication.h>
#include <QUrl>
#include "GlobalSettings.h"
#include <QtCharts>
#include <QSplineSeries>

BaliseMer::BaliseMer()
{
}

BaliseMer::BaliseMer(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language,
DatasMeteo v_Datas, DatasMeteo v_Summary, vector<DatasMeteo> v_History)
:Balise(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
}

BaliseMer::~BaliseMer()
{
}

DatasMeteo BaliseMer::getDatas()
{
    return datas;
}

vector<DatasMeteo>* BaliseMer::getHistory()
{
    return &history;
}

DatasMeteo BaliseMer::getSummary()
{
    return this->summary;
}

void BaliseMer::requestData()
{
    const auto& url = QUrl("http://" + GlobalSettings::Instance()->getIP() + ":" + GlobalSettings::Instance()->getPort() + "/sensor");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager nam;
    QNetworkReply* reply = nam.get(request);
    
    
    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();
    

    QByteArray response_data = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObject = jsonResponse.object();

    // Temperature
    datas.setTemperatureCelsius(jsonObject["temp"].toDouble());
    
    // Pressure
    datas.setPressure(jsonObject["pres"].toDouble());

    //Humidity
    datas.setHumidity(jsonObject["humi"].toDouble());
}

void BaliseMer::requestMeanData()
{
    QNetworkRequest request(QUrl("http://" + GlobalSettings::Instance()->getIP() + ":" + GlobalSettings::Instance()->getPort() + "/history:12"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager nam;
    QNetworkReply* reply = nam.get(request);


    while (!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();


    QByteArray response_data = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray jsonArray = jsonObject["history"].toArray();

    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        DatasMeteo* ptrDM = new DatasMeteo;
        ptrDM->setTemperatureCelsius(obj["temp"].toDouble());
        ptrDM->setHumidity(obj["humi"].toDouble());
        ptrDM->setPressure(obj["pres"].toDouble());
        qDebug() << "temp:" << ptrDM->getTemperatureCelsius() << " humi: " << ptrDM->getHumidity() << "  pres: " << ptrDM->getPressure();
        this->history.push_back(*ptrDM);
    }

    // Mean Temperature
    double sumTemp = 0.0;
    for (int a = 0; a < history.size(); a++)
    {
        sumTemp += history.at(a).getTemperatureCelsius();   
    }
    setSummary(sumTemp / history.size());   
}

void BaliseMer::setSummary(double vMeanTemp)
{
    this->summary.setTemperatureCelsius(vMeanTemp);
}


QPixmap BaliseMer::displayWeatherIcon()
{
    QPixmap picture;
    QPixmap pictureScaled;

    if (datas.getPressure() <= 1000)
    {
        picture.load(":/new/Default/icons/rain.png");
        pictureScaled = picture.scaledToHeight(90);
    }
    else if ((datas.getPressure() > 1000) && (datas.getPressure() <= 1020))
    {
        picture.load(":/new/Default/icons/clouds.png");
        pictureScaled = picture.scaledToHeight(90);
    }
    else
    {
        picture.load(":/new/Default/icons/sun.png");
        pictureScaled = picture.scaledToHeight(90);
    }
    return pictureScaled;
}

QChartView* BaliseMer::displayDetailedChart()
{
    // Serie Temperature
    QSplineSeries* seriesTemp = new QSplineSeries();
    seriesTemp->setName(QObject::tr("Température"));
    double minTemp = 1000;  // Large enough to cover all case (°C / °F / K)
    double maxTemp = -1000; // Large enough to cover all case (°C / °F / K)
    for (int i = 0; i < getHistory()->size(); i++)
    {
        if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_CELSIUS)
        {
            seriesTemp->append(i, getHistory()->at(i).getTemperatureCelsius());
            if (getHistory()->at(i).getTemperatureCelsius() < minTemp)
            {
                minTemp = getHistory()->at(i).getTemperatureCelsius();
            }
            if (getHistory()->at(i).getTemperatureCelsius() > maxTemp)
            {
                maxTemp = getHistory()->at(i).getTemperatureCelsius();
            }
        }
        else if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_FAHRENHEIT)
        {
            seriesTemp->append(i, getHistory()->at(i).getTemperatureFahrenheit());
            if (getHistory()->at(i).getTemperatureFahrenheit() < minTemp)
            {
                minTemp = getHistory()->at(i).getTemperatureFahrenheit();
            }
            if (getHistory()->at(i).getTemperatureFahrenheit() > maxTemp)
            {
                maxTemp = getHistory()->at(i).getTemperatureFahrenheit();
            }
        }
        else 
        {
            seriesTemp->append(i, getHistory()->at(i).getTemperatureKelvin());
            if (getHistory()->at(i).getTemperatureKelvin() < minTemp)
            {
                minTemp = getHistory()->at(i).getTemperatureKelvin();
            }
            if (getHistory()->at(i).getTemperatureKelvin() > maxTemp)
            {
                maxTemp = getHistory()->at(i).getTemperatureKelvin();
            }
        }
    }

    // Serie Mean Temperature
    QSplineSeries* serieMeanTemp = new QSplineSeries();
    serieMeanTemp->setName(QObject::tr("Température moyenne"));
    if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_CELSIUS)
    {
        serieMeanTemp->append(0, getSummary().getTemperatureCelsius());
        serieMeanTemp->append(getHistory()->size(), getSummary().getTemperatureCelsius());
    }
    else if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_FAHRENHEIT)
    {
        serieMeanTemp->append(0, getSummary().getTemperatureFahrenheit());
        serieMeanTemp->append(getHistory()->size(), getSummary().getTemperatureFahrenheit());
    }
    else
    {
        serieMeanTemp->append(0, getSummary().getTemperatureKelvin());
        serieMeanTemp->append(getHistory()->size(), getSummary().getTemperatureKelvin());
    }
    
    // Serie Pressure
    QSplineSeries* seriePress = new QSplineSeries();
    seriePress->setName(QObject::tr("Pression"));
    int minPress = 2000; // Large enough to cover all case
    int maxPress = 0;
    for (int i = 0; i < getHistory()->size(); i++)
    {
        seriePress->append(i, getHistory()->at(i).getPressure());
        if (getHistory()->at(i).getPressure() < minPress)
        {
            minPress = getHistory()->at(i).getPressure();
        }
        if (getHistory()->at(i).getPressure() > maxPress)
        {
            maxPress = getHistory()->at(i).getPressure();
        }
    }

    // Serie Humidity
    QSplineSeries* serieHumi = new QSplineSeries();
    serieHumi->setName("Humidité");
    int minHumi = 100;
    int maxHumi = 0;
    for (int i = 0; i < getHistory()->size(); i++)
    {
        serieHumi->append(i, getHistory()->at(i).getHumidity());
        if (getHistory()->at(i).getHumidity() < minHumi)
        {
            minHumi = getHistory()->at(i).getHumidity();
        }
        if (getHistory()->at(i).getHumidity() > maxHumi)
        {
            maxHumi = getHistory()->at(i).getHumidity();
        }
    }

    QChart* chart = new QChart();
    chart->addSeries(seriesTemp);
    chart->addSeries(serieMeanTemp);
    chart->addSeries(seriePress);
    chart->addSeries(serieHumi);

    QValueAxis* axisY_Temps = new QValueAxis;
    QValueAxis* axisY_Press = new QValueAxis;
    QValueAxis* axisY_Humi = new QValueAxis;
    QValueAxis* axisX = new QValueAxis;

    axisY_Temps->setRange(minTemp - 0.1, maxTemp + 0.1);
    axisY_Press->setRange(minPress - 1, maxPress + 1);
    axisY_Humi->setRange(minHumi - 10, maxHumi + 10);

    if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_CELSIUS)
    {
        axisY_Temps->setTitleText(QObject::tr("Température (°C)"));
    }
    else if (GlobalSettings::Instance()->getTemperatureUnit() == TemperatureUnitEnum::UNIT_FAHRENHEIT)
    {
        axisY_Temps->setTitleText(QObject::tr("Température (°F)"));
    }
    else
    {
        axisY_Temps->setTitleText(QObject::tr("Température (K)"));
    }
    axisY_Press->setTitleText(QObject::tr("Pression (hPa)"));
    axisY_Humi->setTitleText(QObject::tr("Humidité (%)"));
    
    chart->addAxis(axisY_Temps, Qt::AlignLeft);
    chart->addAxis(axisY_Press, Qt::AlignLeft);
    chart->addAxis(axisY_Humi, Qt::AlignRight);
    chart->addAxis(axisX, Qt::AlignBottom);
    
    seriesTemp->attachAxis(axisY_Temps);
    seriesTemp->attachAxis(axisX);
    serieMeanTemp->attachAxis(axisY_Temps);
    serieMeanTemp->attachAxis(axisX);
    seriePress->attachAxis(axisY_Press);
    seriePress->attachAxis(axisX);
    serieHumi->attachAxis(axisY_Humi);
    serieHumi->attachAxis(axisX);

    chart->setTitle(QObject::tr("Historique des 12 dernières heures"));
    chart->show();

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //chartView->show();
    chartView->resize(700, 400);
    
    return chartView;
}