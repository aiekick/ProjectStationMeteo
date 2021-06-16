#ifndef SETTINGSDLG_H
#define SETTINGSDLG_H

#include <QDialog>

namespace Ui {
class SettingsDlg;
}

class SettingsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDlg(QWidget *parent = nullptr);
    ~SettingsDlg();

private slots:
    void on_cancelBtn_clicked();
    void on_okBtn_clicked();
    void on_applyBtn_clicked();
    void on_rbFormat24H_clicked();
    void on_rbFormat12H_clicked();
    void on_rbUnitCelsius_clicked();
    void on_rbUnitFahrenheit_clicked();
    void on_rbUnitKelvin_clicked();
    void on_cbFontFamily_currentFontChanged(const QFont &vFont);
    void on_cbStyle_activated(const QString &vStyle);
    void on_cbLanguage_activated(const QString &vLanguage);

private:
    bool Init();
    void Unit();
    void ApplyConfig();
    void CheckIfSomethingWasChanged();

private:
    Ui::SettingsDlg *ui;
};

#endif // SETTINGSDLG_H
