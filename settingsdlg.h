#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QWidget>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsDlg(QWidget *parent = nullptr);
    ~SettingsDlg();

private:
    Ui::SettingsDlg *ui;
};

#endif // SETTINGSDLG_H
