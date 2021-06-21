#include "balisevillepanel.h"
#include "ui_balisevillepanel.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QSettings>
#include "widgetvillecurrent.h"
#include "widgetvilleforecast.h"

BaliseVillePanel::BaliseVillePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaliseVillePanel)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
}

BaliseVillePanel::~BaliseVillePanel()
{
    delete ui;
}

void BaliseVillePanel::updatedataville()
{
    objville.Recuperation_Api_Current();
    objville.Recuperation_Api_ForeCast();

    ApplyStyle();
}

void BaliseVillePanel::changeEvent(QEvent *e)
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

void BaliseVillePanel::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }

    // for reload pictures according to style
    ui->jouractu->remplissage(objville.recupimage(objville.getDatasJourActu()));
    ui->jour1->remplissage(objville.recupimage(objville.getDatasForeCast1()));
    ui->jour2->remplissage(objville.recupimage(objville.getDatasForeCast2()));
    ui->jour3->remplissage(objville.recupimage(objville.getDatasForeCast3()));
    ui->jour4->remplissage(objville.recupimage(objville.getDatasForeCast4()));
    ui->jour5->remplissage(objville.recupimage(objville.getDatasForeCast5()));

    ui->jouractu->ApplyStyle();
    ui->jour1->ApplyStyle();
    ui->jour2->ApplyStyle();
    ui->jour3->ApplyStyle();
    ui->jour4->ApplyStyle();
    ui->jour5->ApplyStyle();
}
