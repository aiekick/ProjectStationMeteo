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
    ui->texttempville->setText(temperature);


   QString pression=QString::number( (argu.getPressure()));
   ui->textpressville->setText(pression);

    QString humidite=QString::number( (argu.getHumidity()));

    ui->texthumiville->setText(humidite);



    QString date= argu.getDate();

    ui->textdateville->setText(date);

    QString description= argu.getPicto();

    ui->textdescville->setText(description);



}
