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

QString BaliseVille::getDatas_Description()
{
    return this->datas.getDescription();
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
    this->datas = v_DatasMeteo;
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
    QString datesansheure=0;
     QString Datesansheurecompare=0;


    foreach(const QJsonValue &value, jsonArray)

        {
        //if (i=0)Datesansheurecompare=datesansheure;
    QJsonObject obj = value.toObject();

    QString dates1=obj["dt_txt"].toString();
    QStringList datesdecompose=dates1.split(QRegularExpression("\\s+"));
     datesansheure= datesdecompose[0];

    // if(datesansheure!=Datesansheurecompare)
      //   i++;
    qDebug() <<"datesansheure: "<<datesansheure;

    qDebug() << "date: " << obj["dt_txt"].toString();


    qDebug() << "dt: " << obj["dt"].toInt();


    QJsonObject mainObject = obj["main"].toObject();
    qDebug() << "temp: " << mainObject["temp"].toDouble();
    qDebug() << "humidity: " << mainObject["humidity"].toInt();
    qDebug() << "pressure: " << mainObject["pressure"].toInt();

    QJsonArray weatherArray = obj["weather"].toArray();
    foreach(const QJsonValue &value1, weatherArray)
    {
        QJsonObject obj1 = value1.toObject();

        qDebug() << "description: " << obj1["description"].toString();
        //icon
        qDebug() << "icone: " << obj1["icon"].toString();
         //icon
 //if (i=0)
        //{
        datas.setIcon(obj1["icon"].toString());
        //Picto
        datas.setDescription(obj1["description"].toString());
        // }
/* if (i=1)
 * {
        datas2.setIcon(obj1["icon"].toString());
        //Picto
        datas2.setPicto( obj1["description"].toString());
        }
// if (i=2)
        {
        datas3.setIcon(obj1["icon"].toString());
        //Picto
        datas3.setPicto( obj1["description"].toString());
        }
 // if (i=3)
        {
        datas4.setIcon(obj1["icon"].toString());
        //Picto
        datas4.setPicto( obj1["description"].toString());
        }
// if (i=4)
        {
        datas5.setIcon(obj1["icon"].toString());
        //Picto
        datas5.setPicto( obj1["description"].toString());
        } */

}


//if (i=0)
 // {
   //date
     datas.setDate(datesansheure);

    // Temperature
    datas.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    datas.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas.setHumidity(mainObject["humidity"].toDouble());
   //}

  /* if (i=1)
   {
   //date
     datas2.setDate(datesansheure);

    // Temperature
    datas2.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    datas2.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas2.setHumidity(mainObject["humidity"].toDouble());
   }

 if (i=2)
   {
   //date
     datas3.setDate(datesansheure);

    // Temperature
    datas3.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    data3s.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas3.setHumidity(mainObject["humidity"].toDouble());
   }

 if (i=3)
   {
   //date
     datas4.setDate(datesansheure);

    // Temperature
    datas4.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    datas4.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas4.setHumidity(mainObject["humidity"].toDouble());
   }
 if (i=4)
   {
   //date
     datas5.setDate(datesansheure);

    // Temperature
    datas5.setTemperatureKelvin(mainObject["temp"].toDouble());

    // Pressure
    datas5.setPressure(mainObject["pressure"].toDouble());

    //Humidity
    datas5.setHumidity(mainObject["humidity"].toDouble());
   }


   Datesansheurecompare=datesansheure;

  */

break;
}
}
