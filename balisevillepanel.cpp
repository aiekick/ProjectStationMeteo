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
#include "widgetville.h"

BaliseVillePanel::BaliseVillePanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaliseVillePanel)
{
    ui->setupUi(this);
}

BaliseVillePanel::~BaliseVillePanel()
{
    delete ui;
}

void BaliseVillePanel::updatedataville()
{
    objville.RecuperationApi();
    ui->jouractu->remplissage(objville.recupimage(objville.getDatas()));
    ui->jour2->remplissage(objville.recupimage(objville.getDatas2()));
    ui->jour3->remplissage(objville.recupimage(objville.getDatas3()));
    ui->jour4->remplissage(objville.recupimage(objville.getDatas4()));
    ui->jour5->remplissage(objville.recupimage(objville.getDatas5()));
}
