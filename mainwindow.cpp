#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "infosClient.hpp"
#include "baliseMer.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_UpdateMer_clicked()
{
    /*QNetworkRequest request(QUrl("https://api.openweathermap.org/data/2.5/weather?q=toulouse&appid=a3879d9db90104634c555730c707e83a"));
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

    QJsonArray jsonArray = jsonObject["weather"].toArray();

    foreach(const QJsonValue & value, jsonArray)
    {
        QJsonObject obj = value.toObject();
        qDebug() << "id : " << obj["id"].toInt();
        qDebug() << "main : " << obj["main"].toString();
        qDebug() << "description : " << obj["description"].toString();
        qDebug() << "--------------------";
    }

    QJsonObject objectMain = jsonObject["main"].toObject();

    qDebug() << "temp : " << objectMain["temp"].toDouble();
    qDebug() << "pression : " << objectMain["pressure"].toInt();
    qDebug() << "humidite : " << objectMain["humidity"].toInt();


    DatasMeteo dm1;
    DatasMeteo dm2;
    vector<DatasMeteo> dm3;
    BaliseMer bm1(1,2,"24", "","","",dm1,dm2,dm3);
    // Temperature
    bm1.setTemperature(objectMain["temp"].toDouble());
    QString temp = QString::number(bm1.getTemperature());
    this->ui->label_Temperature_Mer->setText(temp);
    // Pressure
    bm1.setPressure(objectMain["pressure"].toInt());
    QString press = QString::number(bm1.getPressure());
    this->ui->label_Pressure_Mer->setText(press);
    //Humidity
    bm1.setHumidity(objectMain["humidity"].toInt());
    QString humi = QString::number(bm1.getHumidity());
    this->ui->label_Humidity_Mer->setText(humi);*/


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
    //QJsonObject objectMain = jsonObject["main"].toObject();

    DatasMeteo dm1;
    DatasMeteo dm2;
    vector<DatasMeteo> dm3;
    BaliseMer bm1(1, 2, "24", "", "", "", dm1, dm2, dm3);
    // Temperature
    bm1.setTemperature(jsonObject["temp"].toDouble());
    QString temp = QString::number(bm1.getTemperature());
    this->ui->label_Temperature_Mer->setText(temp);
    // Pressure
    bm1.setPressure(jsonObject["pres"].toDouble());
    QString press = QString::number(bm1.getPressure());
    this->ui->label_Pressure_Mer->setText(press);
    //Humidity
    bm1.setHumidity(jsonObject["humi"].toDouble());
    QString humi = QString::number(bm1.getHumidity());
    this->ui->label_Humidity_Mer->setText(humi);
}
