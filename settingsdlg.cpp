#include "settingsdlg.h"
#include "ui_settingsdlg.h"

SettingsDlg::SettingsDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);
}

SettingsDlg::~SettingsDlg()
{
    delete ui;
}
