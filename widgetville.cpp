#include "widgetville.h"
#include "ui_widgetville.h"

WidgetVille::WidgetVille(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVille)
{
    ui->setupUi(this);
}

WidgetVille::~WidgetVille()
{
    delete ui;
}

void WidgetVille::remplissage(DatasMeteo argu)
{


    QString temperature;
    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_CELSIUS )
    {
        temperature=QString::number((argu.getTemperatureCelsius()));
        ui->texttempville->setText(temperature+" °C");
    }
    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_FAHRENHEIT )
    {
        temperature=QString::number((argu.getTemperatureFahrenheit()));
        ui->texttempville->setText(temperature+" °F");
    }
    if (GlobalSettings::Instance()->getTemperatureUnit()==TemperatureUnitEnum::UNIT_KELVIN )
    {
        temperature=QString::number((argu.getTemperatureKelvin()));
        ui->texttempville->setText(temperature+" °K");
    }





    ui->texttempville->setText(argu.getTemperatureToStringFromSettings());


    QString pression=QString::number( (argu.getPressure()));
    ui->textpressville->setText(pression+" hpa");

    QString humidite=QString::number( (argu.getHumidity()));
    ui->texthumiville->setText(humidite+" %");



    QString date= argu.getDate();
    ui->textdateville->setText(date);

    QString description= argu.getDescription();
    ui->textdescville->setText(description);

 ui->labelicone->setPixmap(argu.getImage());

}
