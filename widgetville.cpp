#include "widgetville.h"
#include "ui_widgetville.h"
#include <QWidget>


widgetville::widgetville(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widgetville)
{
    ui->setupUi(this);
}

widgetville::~widgetville()
{
    delete ui;
}

void widgetville::remplissage(DatasMeteo argu)
{
    QString temperature=QString::number((argu.getTemperatureCelsius()));

    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_CELSIUS )

        ui->texttempville->setText(temperature+" °C");
    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_FAHRENHEIT )
        ui->texttempville->setText(temperature+" °F");

    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_KELVIN )
        ui->texttempville->setText(temperature+" °K");


    QString pression=QString::number( (argu.getPressure()));
    ui->textpressville->setText(pression+" hpa");

    QString humidite=QString::number( (argu.getHumidity()));

    ui->texthumiville->setText(humidite+" %");



    QString date= argu.getDate();

    ui->textdateville->setText(date);

    QString description= argu.getPicto();

    ui->textdescville->setText(description);



}
