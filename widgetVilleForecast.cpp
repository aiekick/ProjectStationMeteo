#include "widgetvilleforecast.h"
#include "ui_widgetvilleforecast.h"

#include <QDate>
#include <QPainter>
#include <QStyleOption>

WidgetVilleForecast::WidgetVilleForecast(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVilleForecast)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
}

WidgetVilleForecast::~WidgetVilleForecast()
{
    delete ui;
}

// for permit the apply of stylesheet
void WidgetVilleForecast::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void WidgetVilleForecast::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }
}

void WidgetVilleForecast::remplissage(DatasMeteo vDatas)
{
    ui->texttempvillemin->setText(vDatas.getTemperatureMinToStringFromSettings());
    ui->texttempville->setText(vDatas.getTemperatureToStringFromSettings());
    ui->textpressville->setText(QString::number((vDatas.getPressure())) + " hpa");
    ui->texthumiville->setText(QString::number((vDatas.getHumidity())) + " %");
    ui->labelicone->setPixmap(vDatas.getImage());

    // on va inserer un retour a la ligne dans les espaces
    ui->textdescville->setText(vDatas.getDescription());

    // on affiche juste le jour
    const auto& date = QDate::fromString(vDatas.getDate(), "yyyy-MM-dd");
    ui->textdateville->setText(date.toString("ddd"));
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void WidgetVilleForecast::changeEvent(QEvent *e)
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
