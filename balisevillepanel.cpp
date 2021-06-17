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
    jouractu=new widgetville(this);
    ui->layoutville->addWidget(jouractu);


}

BaliseVillePanel::~BaliseVillePanel()
{
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
    jouractu->remplissage(objville.getDatas());



}
