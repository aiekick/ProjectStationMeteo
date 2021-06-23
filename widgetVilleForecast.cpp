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
    const auto& fontFamily = GlobalSettings::Instance()->getFontFamily();

    // regroupé par taille de font
    auto labelFont = ui->textdateville->font();
    labelFont.setFamily(fontFamily);
    ui->textdateville->setFont(labelFont);
    ui->textdescville->setFont(labelFont);
    ui->texthumiville->setFont(labelFont);
    ui->textpressville->setFont(labelFont);
    ui->texttempville->setFont(labelFont);
    ui->texttempvillemin->setFont(labelFont);

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

    // on affiche juste le jour traduit dans la bonne langue
    const auto& date = QDate::fromString(vDatas.getDate(), "yyyy-MM-dd");
    if (GlobalSettings::Instance()->getLanguage() == "FR")
    {
        ui->textdateville->setText(QLocale("fr_FR").toString(date, "ddd"));
    }
    else if (GlobalSettings::Instance()->getLanguage() == "EN")
    {
        ui->textdateville->setText(QLocale("en_EN").toString(date, "ddd"));
    }
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
