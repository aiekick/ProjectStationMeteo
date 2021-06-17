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
#include "GlobalSettings.h"

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
    QString temperature = baliseMer.getDatas().displayCorrectUnit();
    this->ui->label_Temperature_Mer->setText(temperature);

    // Pressure
    QString pressure = QString::number(baliseMer.getDatas().getPressure());
    this->ui->label_Pressure_Mer->setText(pressure + " hPa");

    //Humidity
    QString humidity = QString::number(baliseMer.getDatas().getHumidity());
    this->ui->label_Humidity_Mer->setText(humidity + " %");

    // Mean Temperature
    QString meanTemperature = baliseMer.getSummary().displayCorrectUnit();
    this->ui->label_Mean_Temperature_Mer->setText(meanTemperature);
    baliseMer.getHistory()->clear();
}

void BaliseMerPanel::on_pushButton_Refresh_clicked()
{
    baliseMer.requestData();
    baliseMer.requestMeanData();
    updateData();
}