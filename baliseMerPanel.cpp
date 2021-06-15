#include "baliseMerPanel.h"
#include "ui_baliseMerPanel.h"
#include "balise.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>

BaliseMerPanel::BaliseMerPanel(QWidget *parent)
    : QWidget(parent), ui(new Ui::baliseMerPanel)
{
	ui->setupUi(this);
}

BaliseMerPanel::~BaliseMerPanel()
{
	delete ui;
}

void BaliseMerPanel::updateData()
{
    // Temperature
    QString temperature = QString::number(baliseMer.getDatas().getTemperatureCelsius());
    this->ui->label_Temperature_Mer->setText(temperature);

    // Pressure
    QString pressure = QString::number(baliseMer.getDatas().getPressure());
    this->ui->label_Pressure_Mer->setText(pressure);

    //Humidity
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    this->ui->label_Humidity_Mer->setText(humidity);

    /*
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
    */
}

void BaliseMerPanel::on_pushButton_Refresh_clicked()
{
    baliseMer.requestData();
    updateData();
}

void BaliseMerPanel::on_pushButton_Degrees_clicked()
{ 
    /*
    static int a = 0;

    if (a == 0) // Celsius to Fahrenheit
    {
        baliseMer.requestData();
        updateData();

        QString temp = this->ui->label_Temperature_Mer->text();
        double newTemp = QString::number(temp);


        a = 1;
    }
    else // Fahrenheit to Celsius
    {
       
        a = 0;
    }
    */
}
