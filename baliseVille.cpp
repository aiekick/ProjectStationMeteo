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


DatasMeteo &BaliseVille::getDatas2()
{
    return datas2;
}

DatasMeteo &BaliseVille::getDatas3()
{
    return datas3;
}

DatasMeteo &BaliseVille::getDatas4()
{
    return datas4;
}

DatasMeteo &BaliseVille::getDatas5()
{
    return datas5;
}

void BaliseVille::setDatas(DatasMeteo v_DatasMeteo)
{
    this->datas = v_DatasMeteo;
}

void BaliseVille::RecuperationApi()
{
    double tempcumul1=0;
    double tempmoy1=0;
 int pression1cumul=0;
 int pression1moyenne=0;
 int humidite1cumul=0;
 int humidite1moyenne=0;
 double tempcumul2=0;
 double tempmoy2=0;
int pression2cumul=0;
int pression2moyenne=0;
int humidite2cumul=0;
int humidite2moyenne=0;
double tempcumul3=0;
double tempmoy3=0;
int pression3cumul=0;
int pression3moyenne=0;
int humidite3cumul=0;
int humidite3moyenne=0;
double tempcumul4=0;
double tempmoy4=0;
int pression4cumul=0;
int pression4moyenne=0;
int humidite4cumul=0;
int humidite4moyenne=0;
double tempcumul5=0;
double tempmoy5=0;
int pression5cumul=0;
int pression5moyenne=0;
int humidite5cumul=0;
int humidite5moyenne=0;


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


    QJsonObject obj = value.toObject();

    QString dates1=obj["dt_txt"].toString();
    QStringList datesdecompose=dates1.split(QRegularExpression("\\s+"));
     datesansheure= datesdecompose[0];

    if(datesansheure!=Datesansheurecompare){
        i++;
    j=1;
    }

    if(datesansheure==Datesansheurecompare)
        j++;


    qDebug() <<"datesansheure: "<<datesansheure;

    qDebug() << "date: " << obj["dt_txt"].toString();


    qDebug() << "dt: " << obj["dt"].toInt();


    QJsonObject mainObject = obj["main"].toObject();
    qDebug() << "temp: " << mainObject["temp"].toDouble();
    qDebug() << "humidity: " << mainObject["humidity"].toInt();
    qDebug() << "pressure: " << mainObject["pressure"].toInt();

    QJsonArray weatherArray = obj["weather"].toArray();
    foreach(const QJsonValue &value1, weatherArray)
    {  /*if(datesansheure!=Datesansheurecompare)
           i++;*/
        QJsonObject obj1 = value1.toObject();

        qDebug() << "description: " << obj1["description"].toString();
        //icon
        qDebug() << "icone: " << obj1["icon"].toString();
         //icon
 if (i==1)
        {
        datas.setIcon(obj1["icon"].toString());
        //Picto
        datas.setDescription(obj1["description"].toString());






         }
 if (i==2)
  {
        datas2.setIcon(obj1["icon"].toString());
        //Picto
        datas2.setDescription( obj1["description"].toString());

        }
 if (i==3)
        {
        datas3.setIcon(obj1["icon"].toString());
        //Picto
        datas3.setDescription( obj1["description"].toString());
        }
  if (i==4)
        {
        datas4.setIcon(obj1["icon"].toString());
        //Picto
        datas4.setDescription( obj1["description"].toString());
        }
 if (i==5)
        {
        datas5.setIcon(obj1["icon"].toString());
        //Picto
        datas5.setDescription( obj1["description"].toString());
        }

}


if (i==1)
  {
   //date
     datas.setDate(datesansheure);

    // Temperature
     tempcumul1+=(mainObject["temp"].toDouble());
     tempmoy1=(tempcumul1/j);
    datas.setTemperatureKelvin(tempmoy1);
    // Pressure
    pression1cumul+=mainObject["pressure"].toDouble();
    pression1moyenne=pression1cumul/j;
    datas.setPressure(pression1moyenne);
    //Humidity
    humidite1cumul+=mainObject["humidity"].toDouble();
      humidite1moyenne=humidite1cumul/j;
    datas.setHumidity(humidite1moyenne);
   }

   if (i==2)
   {
   //date
     datas2.setDate(datesansheure);

    // Temperature
     tempcumul2+=(mainObject["temp"].toDouble());
     tempmoy2=(tempcumul2/j);
    datas2.setTemperatureKelvin(tempmoy2);

    // Pressure
    pression2cumul+=mainObject["pressure"].toDouble();
    pression2moyenne=pression2cumul/j;
    datas2.setPressure(pression2moyenne);

    //Humidity
    humidite2cumul+=mainObject["humidity"].toDouble();
      humidite2moyenne=humidite2cumul/j;
    datas2.setHumidity(humidite2moyenne);
   }

 if (i==3)
   {
   //date
     datas3.setDate(datesansheure);

    // Temperature
     tempcumul3+=(mainObject["temp"].toDouble());
     tempmoy3=(tempcumul3/j);
    datas3.setTemperatureKelvin(tempmoy3);

    // Pressure
    pression3cumul+=mainObject["pressure"].toDouble();
    pression3moyenne=pression3cumul/j;
    datas3.setPressure(pression3moyenne);

    //Humidity
    humidite3cumul+=mainObject["humidity"].toDouble();
      humidite3moyenne=humidite3cumul/j;
    datas3.setHumidity(humidite3moyenne);
   }

 if (i==4)
   {
   //date
     datas4.setDate(datesansheure);

    // Temperature
     tempcumul4+=(mainObject["temp"].toDouble());
     tempmoy4=(tempcumul4/j);
    datas4.setTemperatureKelvin(tempmoy4);

    // Pressure
    pression4cumul+=mainObject["pressure"].toDouble();
    pression4moyenne=pression4cumul/j;
    datas4.setPressure(pression4moyenne);

    //Humidity
    humidite4cumul+=mainObject["humidity"].toDouble();
      humidite4moyenne=humidite4cumul/j;
    datas4.setHumidity(humidite4moyenne);
   }
 if (i==5)
   {
   //date
     datas5.setDate(datesansheure);

    // Temperature
     tempcumul5+=(mainObject["temp"].toDouble());
     tempmoy5=(tempcumul5/j);
    datas5.setTemperatureKelvin(tempmoy5);

    // Pressure
    pression5cumul+=mainObject["pressure"].toDouble();
    pression5moyenne=pression5cumul/j;
    datas5.setPressure(pression5moyenne);

    //Humidity
    humidite5cumul+=mainObject["humidity"].toDouble();
      humidite5moyenne=humidite5cumul/j;
    datas5.setHumidity(humidite5moyenne);
   }


   Datesansheurecompare=datesansheure;




    }
}

DatasMeteo BaliseVille::recupimage(DatasMeteo dataimage)
{


    QPixmap image;
    QPixmap imageScaled;


        image.load(":/new/Default/icons/"+dataimage.getIcon()+".png");
        imageScaled = image.scaledToHeight(90);
        dataimage.setImage(imageScaled);






return dataimage;

}













