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

void BaliseVillePanel::on_pushButtonville_clicked()
{
    QString ville2=ui->textville->text();
    objville.getDatas().setVille(ville2);

objville.RecuperationApi();


}

