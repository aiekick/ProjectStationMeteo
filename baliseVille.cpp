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
#include <QUrl>


#include <qdatetime.h>

#include "datasMeteo.h"
#include "GlobalSettings.h"

BaliseVille::BaliseVille() : Balise()
{
}

BaliseVille::~BaliseVille()
{
}
QVector<DatasMeteo>* BaliseVille::getHistorique()
{
    return &historique;
}
DatasMeteo &BaliseVille::getDatasJourActu()
{
    return datasJourActu;
}

DatasMeteo &BaliseVille::getDatasForeCast1()
{
    return datasForeCast1;
}

DatasMeteo &BaliseVille::getDatasForeCast2()
{
    return datasForeCast2;
}

DatasMeteo &BaliseVille::getDatasForeCast3()
{
    return datasForeCast3;
}

DatasMeteo &BaliseVille::getDatasForeCast4()
{
    return datasForeCast4;
}

DatasMeteo &BaliseVille::getDatasForeCast5()
{
    return datasForeCast5;
}

void BaliseVille::setDatasJourActu(DatasMeteo v_DatasMeteo)
{
    this->datasJourActu = v_DatasMeteo;
}

void BaliseVille::Recuperation_Api_Current()
{
    /////////// send api request ///////////////////////

    QNetworkRequest request(getWeatherDayUrl());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /////////// wait response //////////////////////////

    QNetworkAccessManager nam;
    QNetworkReply *reply = nam.get(request);
    while(!reply->isFinished())
    {
        qApp->processEvents();
    }
    reply->deleteLater();

    /////////// response received //////////////////////

    QByteArray response_data = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(response_data);
    QJsonObject jo_response = jsonResponse.object();
    if (!jo_response.isEmpty())
    {
        QJsonArray ja_weather = jo_response["weather"].toArray();
        if (!ja_weather.isEmpty())
        {
            QJsonObject jo_weather = ja_weather[0].toObject();
            if (!jo_weather.isEmpty())
            {
                datasJourActu.setIcon(jo_weather["icon"].toString());
                datasJourActu.setDescription( jo_weather["description"].toString());
            }
        }

        QJsonObject jo_main = jo_response["main"].toObject();
        if (!jo_main.isEmpty())
        {
            datasJourActu.setTemperatureKelvin(jo_main["temp"].toDouble());
            datasJourActu.setPressure(jo_main["pressure"].toInt());
            datasJourActu.setHumidity(jo_main["humidity"].toInt());
        }

        datasJourActu.setVille(jo_response["name"].toString());
    }
}

void BaliseVille::Recuperation_Api_ForeCast()
{
    int i=0;
    int j=1;
    double tempmin1=1000;
    double tempmax1=0;
    double temp1=0;
    int pression1cumul=0;
    int pression1moyenne=0;
    int humidite1cumul=0;
    int humidite1moyenne=0;
    double tempmin2=1000;
    double tempmax2=0;
    double temp2=0;
    int pression2cumul=0;
    int pression2moyenne=0;
    int humidite2cumul=0;
    int humidite2moyenne=0;
    double tempmin3=1000;
    double tempmax3=0;
    double temp3=0;
    int pression3cumul=0;
    int pression3moyenne=0;
    int humidite3cumul=0;
    int humidite3moyenne=0;
    double tempmin4=1000;
    double tempmax4=0;
    double temp4=0;
    int pression4cumul=0;
    int pression4moyenne=0;
    int humidite4cumul=0;
    int humidite4moyenne=0;
    double tempmin5=1000;
    double tempmax5=0;
    double temp5=0;
    int pression5cumul=0;
    int pression5moyenne=0;
    int humidite5cumul=0;
    int humidite5moyenne=0;

    qDebug() << "SSL ? " << QSslSocket::supportsSsl();

    QNetworkRequest request(getForeCastDayUrl());
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







    QString datesansheure=0;
    QString Datesansheurecompare=0;
QString heuresansdate=0;



    foreach(const QJsonValue &value, jsonArray)
    {
        QJsonObject obj = value.toObject();

        QString dates1=obj["dt_txt"].toString();
        QStringList datesdecompose=dates1.split(QRegularExpression("\\s+"));
        datesansheure= datesdecompose[0];
heuresansdate=datesdecompose[1];
QStringList heureliste=heuresansdate.split(QLatin1Char(':'));
//qDebug() <<heureliste[0];
QString stringheureseuleprevision=heureliste[0];
double heureseuleprevision=stringheureseuleprevision.toDouble();
 QString heureactuelstring= QTime::currentTime().toString("hh");
 double heureactuelle=heureactuelstring.toDouble();
 double heurediff=heureactuelle-heureseuleprevision;
        if(datesansheure!=Datesansheurecompare)
        {
            i++;
            j=1;
        }

        if(datesansheure==Datesansheurecompare)
            j++;

 //qDebug() <<datesdecompose[1];
        // qDebug() <<"datesansheure: "<<datesansheure;
        //qDebug() << "date: " << obj["dt_txt"].toString();
        //qDebug() << "dt: " << obj["dt"].toInt();

        QJsonObject mainObject = obj["main"].toObject();
        // qDebug() << "temp: " << mainObject["temp"].toDouble();
        //  qDebug() << "humidity: " << mainObject["humidity"].toInt();
        //  qDebug() << "pressure: " << mainObject["pressure"].toInt();

        QJsonArray weatherArray = obj["weather"].toArray();
        foreach(const QJsonValue &value1, weatherArray)
        {  /*if(datesansheure!=Datesansheurecompare)
           i++;*/
            QJsonObject obj1 = value1.toObject();

            //qDebug() << "description: " << obj1["description"].toString();
            //icon
            //   qDebug() << "icone: " << obj1["icon"].toString();
            //icon

           // QString heure=QTime::currentTime().toString("hh");
            //qDebug() << heure;
            if (i==1 && heurediff>-2 && heurediff<2)
            {
qDebug()<<"difference : "<<heurediff<<"heure actu: "<< heureactuelle <<"heureeseuleprevisiondecomp : "<<heureseuleprevision;
                datasForeCast1.setIcon(obj1["icon"].toString());
                //Picto
                datasForeCast1.setDescription(obj1["description"].toString());
            }





            else if (i==2 && datesdecompose[1]=="12:00:00" )
            {
                datasForeCast2.setIcon(obj1["icon"].toString());
                //Picto
                datasForeCast2.setDescription( obj1["description"].toString());
            }
            else if (i==3 && datesdecompose[1]=="12:00:00")
            {
                datasForeCast3.setIcon(obj1["icon"].toString());
                //Picto
                datasForeCast3.setDescription( obj1["description"].toString());
            }
            else if (i==4 && datesdecompose[1]=="12:00:00")
            {
                datasForeCast4.setIcon(obj1["icon"].toString());
                //Picto
                datasForeCast4.setDescription( obj1["description"].toString());
            }
            else if (i==5 && datesdecompose[1]=="12:00:00")
            {
                datasForeCast5.setIcon(obj1["icon"].toString());
                //Picto
                datasForeCast5.setDescription( obj1["description"].toString());
            }
        }

        if (i==1)
        {
            //date
            datasForeCast1.setDate(datesansheure);

            // Temperature min
            temp1=(mainObject["temp"].toDouble());
            if(temp1<tempmin1)
                tempmin1=temp1;
            // Temperature max
            if(temp1>tempmax1)
                tempmax1=temp1;
                        datasForeCast1.setTemperatureMinKelvin(tempmin1);
                        datasForeCast1.setTemperatureKelvin(tempmax1);

            // Pressure
            pression1cumul+=mainObject["pressure"].toDouble();
            pression1moyenne=pression1cumul/j;
            datasForeCast1.setPressure(pression1moyenne);
            //Humidity
            humidite1cumul+=mainObject["humidity"].toDouble();
            humidite1moyenne=humidite1cumul/j;
            datasForeCast1.setHumidity(humidite1moyenne);
        }

        if (i==2)
        {
            //date
            datasForeCast2.setDate(datesansheure);

            // Temperature min
            temp2=(mainObject["temp"].toDouble());
            if(temp2<tempmin2)
                tempmin2=temp2;
            // Temperature max
            if(temp2>tempmax2)
                tempmax2=temp2;
                        datasForeCast2.setTemperatureMinKelvin(tempmin2);
                        datasForeCast2.setTemperatureKelvin(tempmax2);


            // Pressure
            pression2cumul+=mainObject["pressure"].toDouble();
            pression2moyenne=pression2cumul/j;
            datasForeCast2.setPressure(pression2moyenne);

            //Humidity
            humidite2cumul+=mainObject["humidity"].toDouble();
            humidite2moyenne=humidite2cumul/j;
            datasForeCast2.setHumidity(humidite2moyenne);
        }

        if (i==3)
        {
            //date
            datasForeCast3.setDate(datesansheure);

            // Temperature
            // Temperature min
            temp3=(mainObject["temp"].toDouble());
            if(temp3<tempmin3)
                tempmin3=temp3;
            // Temperature max
            if(temp3>tempmax3)
                tempmax3=temp3;
                        datasForeCast3.setTemperatureMinKelvin(tempmin3);
                        datasForeCast3.setTemperatureKelvin(tempmax3);
            // Pressure
            pression3cumul+=mainObject["pressure"].toDouble();
            pression3moyenne=pression3cumul/j;
            datasForeCast3.setPressure(pression3moyenne);

            //Humidity
            humidite3cumul+=mainObject["humidity"].toDouble();
            humidite3moyenne=humidite3cumul/j;
            datasForeCast3.setHumidity(humidite3moyenne);
        }

        if (i==4)
        {
            //date
            datasForeCast4.setDate(datesansheure);

            // Temperature
            // Temperature min
            temp4=(mainObject["temp"].toDouble());
            if(temp4<tempmin4)
                tempmin4=temp4;
            // Temperature max
            if(temp4>tempmax4)
                tempmax4=temp4;
                        datasForeCast4.setTemperatureMinKelvin(tempmin4);
                        datasForeCast4.setTemperatureKelvin(tempmax4);

            // Pressure
            pression4cumul+=mainObject["pressure"].toDouble();
            pression4moyenne=pression4cumul/j;
            datasForeCast4.setPressure(pression4moyenne);

            //Humidity
            humidite4cumul+=mainObject["humidity"].toDouble();
            humidite4moyenne=humidite4cumul/j;
            datasForeCast4.setHumidity(humidite4moyenne);
        }
        if (i==5)
        {
            //date
            datasForeCast5.setDate(datesansheure);

            // Temperature
            // Temperature min
            temp5=(mainObject["temp"].toDouble());
            if(temp5<tempmin5)
                tempmin5=temp5;
            // Temperature max
            if(temp5>tempmax5)
                tempmax5=temp5;
                        datasForeCast5.setTemperatureMinKelvin(tempmin5);
                        datasForeCast5.setTemperatureKelvin(tempmax5);

            // Pressure
            pression5cumul+=mainObject["pressure"].toDouble();
            pression5moyenne=pression5cumul/j;
            datasForeCast5.setPressure(pression5moyenne);

            //Humidity
            humidite5cumul+=mainObject["humidity"].toDouble();
            humidite5moyenne=humidite5cumul/j;
            datasForeCast5.setHumidity(humidite5moyenne);
        }

        Datesansheurecompare=datesansheure;
    }
}

DatasMeteo BaliseVille::recupimage(DatasMeteo dataimage)
{
    QPixmap image;
    image.load(GlobalSettings::Instance()->GetThemeIconPath(dataimage.getIcon()));
    dataimage.setImage(image.scaledToHeight(90));
    return dataimage;
}

QUrl BaliseVille::getWeatherDayUrl()
{
    QString baseUrl = "https://api.openweathermap.org/data/2.5/weather?";

    const auto& ville = GlobalSettings::Instance()->getVille();
    baseUrl += "q=" + ville + ",fr"; // limite a la france

    const auto& apikey = GlobalSettings::Instance()->getApiKey();
    baseUrl += "&appid=" + apikey;

    const auto& lang = GlobalSettings::Instance()->getLanguage();
    baseUrl += "&lang=" + lang; // fr, en, etc.. 2 lettres

    return QUrl(baseUrl);
}

QUrl BaliseVille::getForeCastDayUrl()
{
    QString baseUrl = "https://api.openweathermap.org/data/2.5/forecast?";

    const auto& ville = GlobalSettings::Instance()->getVille();
    baseUrl += "q=" + ville + ",fr"; // limite a la france

    const auto& apikey = GlobalSettings::Instance()->getApiKey();
    baseUrl += "&appid=" + apikey;

    const auto& lang = GlobalSettings::Instance()->getLanguage();
    baseUrl += "&lang=" + lang; // fr, en, etc.. 2 lettres

    return QUrl(baseUrl);
}
