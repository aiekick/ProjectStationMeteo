#include "widgetvillecurrent.h"
#include "ui_widgetvillecurrent.h"

#include <QPainter>
#include <QStyleOption>

WidgetVilleCurrent::WidgetVilleCurrent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetVilleCurrent)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
}

WidgetVilleCurrent::~WidgetVilleCurrent()
{
    delete ui;
}

// for permit the apply of stylesheet
void WidgetVilleCurrent::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void WidgetVilleCurrent::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }
}

void WidgetVilleCurrent::remplissage(DatasMeteo vDatas)
{
    ui->texttempville->setText(vDatas.getTemperatureToStringFromSettings());
    ui->textpressville->setText(QString::number((vDatas.getPressure())) + " hpa");
    ui->texthumiville->setText(QString::number((vDatas.getHumidity())) + " %");
    ui->textdateville->setText(vDatas.getVille());
    ui->textdescville->setText(vDatas.getDescription());
    ui->labelicone->setPixmap(vDatas.getImage());
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void WidgetVilleCurrent::changeEvent(QEvent *e)
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
