#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "GlobalSettings.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->retranslateUi(this);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_closeBtn_clicked()
{
    accept();
}

void AboutDialog::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent:: LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
   }
}

void AboutDialog::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }
}
