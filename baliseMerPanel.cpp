#include "baliseMerPanel.h"
#include "ui_baliseMerPanel.h"
#include "balise.h"
#include "baliseMer.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>

baliseMerPanel::baliseMerPanel(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::baliseMerPanel)
{
	ui->setupUi(this);
	QWidget::setWindowTitle("Balise mer panel");
}

baliseMerPanel::~baliseMerPanel()
{
	delete ui;
}

void baliseMerPanel::updateData()
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
    // Pushbutton degrees
    QString degrees = "°F";
    if (this->ui->pushButton_Degrees->text() == degrees)
    {
        QString temp = this->ui->label_Temperature_Mer->text();
        double newTemp = temp.toDouble();
        newTemp += 32;
        temp = QString::number(newTemp);
        this->ui->label_Temperature_Mer->setText(temp);
        this->ui->pushButton_Degrees->setText("°F");
    }
}

void baliseMerPanel::on_pushButton_Refresh_clicked()
{
    baliseMerPanel::updateData();
}

void baliseMerPanel::on_pushButton_Degrees_clicked()
{ 
    static int a = 0;

    if (a == 0) // Celsius to Fahrenheit
    {
        baliseMerPanel::updateData();
        QString temp = this->ui->label_Temperature_Mer->text();
        double newTemp = temp.toDouble();
        newTemp += 32;
        temp = QString::number(newTemp);
        this->ui->label_Temperature_Mer->setText(temp);
        this->ui->pushButton_Degrees->setText("°F");
        a = 1;
    }
    else // Fahrenheit to Celsius
    {
        this->ui->pushButton_Degrees->setText("°C");
        baliseMerPanel::updateData();
        a = 0;
    }
}