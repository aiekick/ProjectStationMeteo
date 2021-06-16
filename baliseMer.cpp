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

void BaliseMer::requestData()
{
    QNetworkRequest request(QUrl("http://82.65.244.166:48001/sensor"));
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
    QNetworkRequest request(QUrl("http://82.65.244.166:48001/history:12"));
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
    int i = 1;
    qDebug() << "before:" << history.size();

    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        
        qDebug() << "----------" << i++;
        qDebug() << "temp: " << obj["temp"].toDouble();
        qDebug() << "pres: " << obj["pres"].toDouble();
        qDebug() << "humi: " << obj["humi"].toDouble();
        DatasMeteo* ptrDM = new DatasMeteo;
        ptrDM->setTemperatureCelsius(obj["temp"].toDouble());
        this->history.push_back(*ptrDM);

    }
    qDebug() << "after:" << history.size();
    qDebug() << "xxxxxxxxxxxxxxxxxxxx";

    for (int a = 0; a < history.size(); a++)
    {
        qDebug() << history.at(a).getTemperatureCelsius();
    }

    // Mean Temperature
    double sumTemp = 0.0;
    for (int a = 0; a < history.size(); a++)
    {
        qDebug() << "Test : " << a + 1 << history.at(a).getTemperatureCelsius();
        sumTemp += history.at(a).getTemperatureCelsius();   
    }

    setMeanTemp(sumTemp / history.size());
    qDebug() << "sumTemp: " << sumTemp;
    qDebug() << "history.size :" << history.size();
    qDebug() << "meanTemp:" << getMeanTemp();
    //qDebug() << "before" << history.size();
    //history.clear(); // Remise a zero du conteneur
    //qDebug() << "after" << history.size();


}

vector<DatasMeteo>* BaliseMer::getHistory()
{
    return &history;
}

double BaliseMer::getMeanTemp()
{
    return this->meanTemp;
}

void BaliseMer::setMeanTemp(double vMeanTemp)
{
    this->meanTemp = vMeanTemp;
}