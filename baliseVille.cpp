#include "baliseVille.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QSettings>
#include <QApplication>

#include "datasMeteo.h"

BaliseVille::BaliseVille() : Balise()
{
}

BaliseVille::BaliseVille(int v_resolution, int v_temperatureUnit, string v_hourFormat, string v_fontFamily, string v_displayStyle, string v_language, DatasMeteo v_DatasMeteo)
:Balise(v_resolution, v_temperatureUnit, v_hourFormat, v_fontFamily, v_displayStyle, v_language)
{
    setDatas(v_DatasMeteo);
}

BaliseVille::~BaliseVille()
{
}

QString BaliseVille::getDatas_Picto()
{
    return this->datas.getPicto();
}

double BaliseVille::getDatas_Temperature()
{
    return this->datas.getTemperatureCelsius();
}

int BaliseVille::getDatas_Humidity()
{
    return this->datas.getHumidity();
}

int BaliseVille::getDatas_Pressure()
{
    return this->datas.getPressure();
}

QString BaliseVille::getDatas_date()
{

return this->datas.getDate();
}

DatasMeteo &BaliseVille::getDatas()
{
    return datas;
}


void BaliseVille::setDatas(DatasMeteo v_DatasMeteo)
{
    this->datas.setPicto(v_DatasMeteo.getPicto());
    this->datas.setTemperatureCelsius(v_DatasMeteo.getTemperatureCelsius());
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

    //Conversion du ByteArray en Json
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);


    QJsonObject jsonObject = jsonResponse.object();


    qDebug() <<"cod : "<< jsonObject["cod"].toString();
    qDebug() <<"message :"<< jsonObject["message"].toInt();
    qDebug() <<"cnt :"<< jsonObject["cnt"].toInt();



    QJsonArray jsonArray = jsonObject["list"].toArray();
    qDebug() << "nb:" << jsonArray.count();



 /* foreach(const QJsonValue &value, jsonArray)

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






    }*/


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
        //Picto
        qDebug() << "description: " << obj1["description"].toString();
        datas.setPicto( obj1["description"].toString());
        //icon
        qDebug() << "icone: " << obj1["icon"].toString();
        datas.setIcon(obj1["icon"].toString());


    }


    //date
    datas.setDate(obj["dt_txt"].toString());


    // Temperature
    datas.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    datas.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas.setHumidity(mainObject["humidity"].toDouble());

     //date
    datas.setDate(obj["dt_txt"].toString());

    break;
}


}

