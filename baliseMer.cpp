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

#include <QObject>

BaliseMer::BaliseMer()
{
}

BaliseMer::~BaliseMer()
{
}

DatasMeteo BaliseMer::getDatas()
{
    return datas;
}

QVector<DatasMeteo>* BaliseMer::getHistory()
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

    // Mean Temperature
    history.clear();
    double sumTemp = 0.0;
    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        DatasMeteo* ptrDM = new DatasMeteo;
        ptrDM->setTemperatureCelsius(obj["temp"].toDouble());
        ptrDM->setHumidity(obj["humi"].toDouble());
        ptrDM->setPressure(obj["pres"].toDouble());
        //qDebug() << "temp:" << ptrDM->getTemperatureCelsius() << " humi: " << ptrDM->getHumidity() << "  pres: " << ptrDM->getPressure();
        history.push_front(*ptrDM);
        sumTemp += ptrDM->getTemperatureCelsius();
    }
    this->summary.setTemperatureCelsius(sumTemp / history.size());
}

QPixmap BaliseMer::displayWeatherIcon()
{
    QPixmap picture;

    const auto _pressure = datas.getPressure();
    if (_pressure <= 1000)
    {
        picture.load(GlobalSettings::Instance()->GetThemeIconPath("10d")); // ou 010n si on est le soir
    }
    else if ((_pressure > 1000) && (_pressure <= 1020))
    {
        picture.load(GlobalSettings::Instance()->GetThemeIconPath("04d")); // ou 04n si on est le soir
    }
    else
    {
        picture.load(GlobalSettings::Instance()->GetThemeIconPath("01d")); // ou 01n si on est le soir
    }

    return picture.scaledToHeight(90);
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

    axisY_Temps->setRange(minTemp - 0.3, maxTemp + 0.3);
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

QChartView* BaliseMer::humidityChart()
{
    QSplineSeries* serie = new QSplineSeries();
 
    int min = 100;
    int max = 0;
    for (int i = 0; i < getHistory()->size(); i++)
    {
        serie->append(i, getHistory()->at(i).getHumidity());
        if (getHistory()->at(i).getHumidity() < min)
        {
            min = getHistory()->at(i).getHumidity();
        }
        if (getHistory()->at(i).getHumidity() > max)
        {
            max = getHistory()->at(i).getHumidity();
        }
        qDebug() << "humi: " << getHistory()->at(i).getHumidity();
        qDebug() << "humi:" << serie->at(i);
    }

    /*
    ///// OK mais moche /////
    QAreaSeries* series = new QAreaSeries(serieHumi);
    QPen pen(QColor(8, 107, 142));
    pen.setWidth(3);
    series->setPen(pen);
  
    QLinearGradient plotBackground;
    plotBackground.setStart(serieHumi->at(0));
    plotBackground.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    plotBackground.setColorAt(0.0, QColor(38,57,65));
    series->setBrush(plotBackground);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(serieHumi->at(0));
    backgroundGradient.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    backgroundGradient.setColorAt(0.0, QColor(45, 46, 48));
    
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisX()->hide();
    chart->axisY()->hide();
    chart->axes(Qt::Vertical).first()->setRange(minHumi - 1, maxHumi + 1);
    chart->setBackgroundBrush(backgroundGradient);*/


    // Define the color and thickness of the curve
    QPen pen(QColor(8,207,217));
    pen.setWidth(3);
    serie->setPen(pen);
    
    // Define the background color
    QLinearGradient backgroundColor;
    backgroundColor.setStart(serie->at(0));
    backgroundColor.setFinalStop(serie->at(getHistory()->size() - 1));
    backgroundColor.setColorAt(0.0, QColor(45, 46, 48));

    QChart* chart = new QChart();
    chart->addSeries(serie);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisX()->hide();
    chart->axisY()->hide();
    chart->axes(Qt::Vertical).first()->setRange(min - 1, max + 1);
    chart->setBackgroundBrush(backgroundColor);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}

QChartView* BaliseMer::pressureChart()
{
    QSplineSeries* serie = new QSplineSeries();
    int min = 2000;
    int max = 0;
    for (int i = 0; i < getHistory()->size(); i++)
    {
        serie->append(i, getHistory()->at(i).getPressure());
        if (getHistory()->at(i).getPressure() < min)
        {
            min = getHistory()->at(i).getPressure();
        }
        if (getHistory()->at(i).getPressure() > max)
        {
            max = getHistory()->at(i).getPressure();
        }
        qDebug() << "humi: " << getHistory()->at(i).getPressure();
        qDebug() << "humi:" << serie->at(i);
    }

    /*
    ///// OK mais moche /////
    QAreaSeries* series = new QAreaSeries(serieHumi);
    QPen pen(QColor(8, 107, 142));
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient plotBackground;
    plotBackground.setStart(serieHumi->at(0));
    plotBackground.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    plotBackground.setColorAt(0.0, QColor(38,57,65));
    series->setBrush(plotBackground);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(serieHumi->at(0));
    backgroundGradient.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    backgroundGradient.setColorAt(0.0, QColor(45, 46, 48));

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisX()->hide();
    chart->axisY()->hide();
    chart->axes(Qt::Vertical).first()->setRange(minHumi - 1, maxHumi + 1);
    chart->setBackgroundBrush(backgroundGradient);*/


    // Define the color and thickness of the curve
    QPen pen(QColor(206,4,234));
    pen.setWidth(3);
    serie->setPen(pen);

    // Define the background color
    QLinearGradient backgroundColor;
    backgroundColor.setStart(serie->at(0));
    backgroundColor.setFinalStop(serie->at(getHistory()->size() - 1));
    backgroundColor.setColorAt(0.0, QColor(45, 46, 48));

    QChart* chart = new QChart();
    chart->addSeries(serie);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisX()->hide();
    chart->axisY()->hide();
    chart->axes(Qt::Vertical).first()->setRange(min - 1, max + 1);
    chart->setBackgroundBrush(backgroundColor);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    

    return chartView;
}

QChartView* BaliseMer::temperatureChart()
{
    QSplineSeries* serie = new QSplineSeries();
    double min = 1000;
    double max = -1000;
    for (int i = 0; i < getHistory()->size(); i++)
    {
        serie->append(i, getHistory()->at(i).getTemperatureCelsius());
        if (getHistory()->at(i).getTemperatureCelsius() < min)
        {
            min = getHistory()->at(i).getTemperatureCelsius();
        }
        if (getHistory()->at(i).getTemperatureCelsius() > max)
        {
            max = getHistory()->at(i).getTemperatureCelsius();
        }
        qDebug() << "min" << min << "max" << max;
    }

    /*
    ///// OK mais moche /////
    QAreaSeries* series = new QAreaSeries(serieHumi);
    QPen pen(QColor(8, 107, 142));
    pen.setWidth(3);
    series->setPen(pen);

    QLinearGradient plotBackground;
    plotBackground.setStart(serieHumi->at(0));
    plotBackground.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    plotBackground.setColorAt(0.0, QColor(38,57,65));
    series->setBrush(plotBackground);

    QLinearGradient backgroundGradient;
    backgroundGradient.setStart(serieHumi->at(0));
    backgroundGradient.setFinalStop(serieHumi->at(getHistory()->size() - 1));
    backgroundGradient.setColorAt(0.0, QColor(45, 46, 48));

    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->axisX()->hide();
    chart->axisY()->hide();
    chart->axes(Qt::Vertical).first()->setRange(minHumi - 1, maxHumi + 1);
    chart->setBackgroundBrush(backgroundGradient);*/


    // Define the color and thickness of the curve
    QPen pen(QColor(53, 190, 7));
    pen.setWidth(3);
    serie->setPen(pen);

    // Define the background color
    QLinearGradient backgroundColor;
    backgroundColor.setStart(serie->at(0));
    backgroundColor.setFinalStop(serie->at(getHistory()->size() - 1U));
    backgroundColor.setColorAt(0.0, QColor(45, 46, 48));

    QChart* chart = new QChart();
    chart->addSeries(serie);
    chart->legend()->hide();
    chart->createDefaultAxes();
    //chart->axisX()->hide();
    //chart->axisY()->hide();
    chart->axisY()->setGridLineVisible(false);
    chart->axisX()->setGridLineVisible(false);
    chart->axes(Qt::Vertical).first()->setRange(min - 0.2, max + 0.2);
    chart->setBackgroundBrush(backgroundColor);
    chart->layout()->setContentsMargins(0, 0, 0, 0);
    chart->setBackgroundRoundness(0);

    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    return chartView;
}
