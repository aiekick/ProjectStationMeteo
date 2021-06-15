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
    datas.setTemperature(jsonObject["temp"].toDouble());
    
    // Pressure
    datas.setPressure(jsonObject["pres"].toDouble());

    //Humidity
    datas.setHumidity(jsonObject["humi"].toDouble());
}