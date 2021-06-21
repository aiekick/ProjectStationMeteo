#include "widgetville.h"
#include "ui_widgetville.h"

WidgetVille::WidgetVille(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVille)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
}

WidgetVille::~WidgetVille()
{
    delete ui;
}

void WidgetVille::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }
}

void WidgetVille::remplissage(DatasMeteo vDatas)
{
    ui->texttempville->setText(vDatas.getTemperatureToStringFromSettings());
    ui->textpressville->setText(QString::number((vDatas.getPressure())) + " hpa");
    ui->texthumiville->setText(QString::number((vDatas.getHumidity())) + " %");
    ui->textdateville->setText(vDatas.getDate());
    ui->textdescville->setText(vDatas.getDescription());
    ui->labelicone->setPixmap(vDatas.getImage());
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void WidgetVille::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
   }
}
