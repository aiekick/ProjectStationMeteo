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

    void changeEvent(QEvent *e) override;

signals:
    void ApplySettingsChange();

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
    void on_cbLanguage_activated(const QString &vLanguage);
    void on_sbDelay_valueChanged(const int& vRefreshDelayInMinutes);
    void on_edIP_textChanged(const QString &vIp);
    void on_edPort_textChanged(const QString &vPort);
    void on_edApiKey_textChanged(const QString &vApiKey);
    void on_edCity_textChanged(const QString &vVille);
    void on_rbStyleDay_clicked();
    void on_rbStyleNight_clicked();

private:
    bool Init();
    void Unit();
    void ApplyConfig();
    void CheckIfSomethingWasChanged();

private:
    Ui::SettingsDlg *ui;
};

#endif // SETTINGSDLG_H
