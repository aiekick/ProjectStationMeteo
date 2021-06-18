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
    /* jouractu=new widgetville(this);
    ui->layoutville->addWidget(jouractu);

    jour2=new widgetville(this);
    ui->layoutville->addWidget(jour2);
    jour3=new widgetville(this);
    ui->layoutville->addWidget(jour3);
    jour4=new widgetville(this);
    ui->layoutville->addWidget(jour4);
    jour5=new widgetville(this);
    ui->layoutville->addWidget(jour5);*/


}

BaliseVillePanel::~BaliseVillePanel()
{
    /* delete jouractu;
    delete jour2;
    delete jour3;
    delete jour4;
    delete jour5;*/
    delete ui;
}

void BaliseVillePanel::on_pushButtonville_clicked()
{
    updatedataville();
}

void BaliseVillePanel::updatedataville()
{
    QString ville2=ui->textville->text();
    objville.getDatas().setVille(ville2);

    objville.RecuperationApi();
    objville.recupimage(objville.getDatas());
    objville.recupimage(objville.getDatas2());
    objville.recupimage(objville.getDatas3());
    objville.recupimage(objville.getDatas4());
    objville.recupimage(objville.getDatas5());


    ui->jouractu->remplissage( objville.recupimage(objville.getDatas()));
    ui->jour2->remplissage( objville.recupimage(objville.getDatas2()));
    ui->jour3->remplissage( objville.recupimage(objville.getDatas3()));
    ui->jour4->remplissage( objville.recupimage(objville.getDatas4()));
    ui->jour5->remplissage( objville.recupimage(objville.getDatas5()));






}
