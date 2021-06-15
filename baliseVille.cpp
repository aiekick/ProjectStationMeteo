#include "baliseVille.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QSettings>
#include "datasMeteo.h"
#include "balisevillepanel.h"
#include "ui_balisevillepanel.h"



 DatasMeteo &BaliseVille::getDatas()
{
    return datas;
}

BaliseVille::BaliseVille(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language, DatasMeteo v_DatasMeteo)
:Balise(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
    setDatas(v_DatasMeteo);
}

BaliseVille::~BaliseVille()
{
}

string BaliseVille::getDatas_Picto()
{
    return this->datas.getPicto();
}

double BaliseVille::getDatas_Temperature()
{
    return this->datas.getTemperature();
}

int BaliseVille::getDatas_Humidity()
{
    return this->datas.getHumidity();
}

int BaliseVille::getDatas_Pressure()
{
    return this->datas.getPressure();
}

void BaliseVille::setDatas(DatasMeteo v_DatasMeteo)
{
    this->datas.setPicto(v_DatasMeteo.getPicto());
    this->datas.setTemperature(v_DatasMeteo.getTemperature());
    this->datas.setHumidity(v_DatasMeteo.getHumidity());
    this->datas.setPressure(v_DatasMeteo.getPressure());
}
void BaliseVille::RecuperationApi()
{



    qDebug() << "SSL ? " << QSslSocket::supportsSsl();

    QNetworkRequest request(QUrl("http://api.openweathermap.org/data/2.5/forecast/?q="+datas.getVille()+"&appid=58e08b52cadfc9c96fc8354666cec712"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");


    QNetworkAccessManager nam;

    QNetworkReply *reply = nam.get(request);

    while(!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();


    QByteArray response_data = reply->readAll();

    qDebug() << "Size: " << response_data.size();

    //Conversion du ByteArryay en Json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);


    QJsonObject jsonObject = jsonResponse.object();


    qDebug() <<"cod : "<< jsonObject["cod"].toString();
    qDebug() <<"message :"<< jsonObject["message"].toInt();
    qDebug() <<"cnt :"<< jsonObject["cnt"].toInt();



    QJsonArray jsonArray = jsonObject["list"].toArray();
    qDebug() << "nb:" << jsonArray.count();



    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        qDebug() << "dt: " << obj["dt"].toInt();
        qDebug() << "date: " << obj["dt_txt"].toString();


        QJsonObject mainObject = obj["main"].toObject();
        qDebug() << "temp: " << mainObject["temp"].toDouble();
        qDebug() << "humidity: " << mainObject["humidity"].toInt();
        qDebug() << "pressure: " << mainObject["pressure"].toInt();

        QJsonArray weatherArray = obj["weather"].toArray();
        foreach(const QJsonValue &value1, weatherArray)
        {
            QJsonObject obj1 = value1.toObject();
            qDebug() << "description: " << obj1["description"].toString();
        }




    }







}
