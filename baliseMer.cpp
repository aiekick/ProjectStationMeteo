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

    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        DatasMeteo* ptrDM = new DatasMeteo;
        ptrDM->setTemperatureCelsius(obj["temp"].toDouble());
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