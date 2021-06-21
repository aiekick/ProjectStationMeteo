#include "settingsdlg.h"
#include "ui_settingsdlg.h"

#include "GlobalSettings.h"
#include "LangManager.h"

static GlobalSettings::SettingsStruct s_SettingsStruct;

SettingsDlg::SettingsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDlg)
{
    ui->setupUi(this);
    ui->retranslateUi(this);

    Init();
}

SettingsDlg::~SettingsDlg()
{
    Unit();

    delete ui;
}

//////////////////////////////////////
/// PUBLIC
//////////////////////////////////////

/// will apply config and closing dialog
void SettingsDlg::on_okBtn_clicked()
{
    ApplyConfig();
    close();
}

/// will wloce dialog without applying config
void SettingsDlg::on_cancelBtn_clicked()
{
    close();
}

/// will apply config but not closing dialog
void SettingsDlg::on_applyBtn_clicked()
{
    ApplyConfig();
}

void SettingsDlg::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {

    }
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void SettingsDlg::changeEvent(QEvent *e)
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

//////////////////////////////////////
/// PRIVATE
//////////////////////////////////////

bool SettingsDlg::Init()
{
    s_SettingsStruct = GlobalSettings::Instance()->getSettingsStruct();

    // General

    // Format Hour
    if (s_SettingsStruct.m_FormatHourEnum == FormatHourEnum::FORMAT_24H)
        ui->rbFormat24H->setChecked(true);
    else
        ui->rbFormat12H->setChecked(true);

    // Temperature Unit
    if (s_SettingsStruct.m_TemperatureUnit == TemperatureUnitEnum::UNIT_CELSIUS)
        ui->rbUnitCelsius->setChecked(true);
    else if (s_SettingsStruct.m_TemperatureUnit == TemperatureUnitEnum::UNIT_FAHRENHEIT)
        ui->rbUnitFahrenheit->setChecked(true);
    else
        ui->rbUnitKelvin->setChecked(true);

    // Font Family
    ui->cbFontFamily->setFont(QFont(s_SettingsStruct.m_FontFamily));

    // Styles
    if (s_SettingsStruct.m_Style == StyleEnum::STYLE_DAY)
        ui->rbStyleDay->setChecked(true);
    else
        ui->rbStyleNight->setChecked(true);

    // Languages
    auto langs = LangManager::Instance()->getTranslations();
    ui->cbLanguage->clear();
    for(const auto& key : langs)
    {
        ui->cbLanguage->addItem(key.first);
    }
    ui->cbLanguage->setCurrentText(s_SettingsStruct.m_Language);

    // Timer Delay
    ui->sbDelay->setValue(s_SettingsStruct.m_RefreshDelayInMinutes);

    // Panel Mer
    ui->edIP->setText(s_SettingsStruct.m_IP);
    ui->edPort->setText(s_SettingsStruct.m_Port);

    // Panel Ville
    ui->edApiKey->setText(s_SettingsStruct.m_ApiKey);
    ui->edCity->setText(s_SettingsStruct.m_Ville);

    return true;
}

void SettingsDlg::Unit()
{

}

void SettingsDlg::ApplyConfig()
{
    GlobalSettings::Instance()->setSettingsStruct(s_SettingsStruct);
    GlobalSettings::Instance()->ApplyStyle(s_SettingsStruct.m_Style);
    LangManager::Instance()->ApplyLang(s_SettingsStruct.m_Language);
    CheckIfSomethingWasChanged();
    emit(SettingsDlg::ApplySettingsChange());
}

void SettingsDlg::CheckIfSomethingWasChanged()
{
    const auto isDiff = GlobalSettings::Instance()->getSettingsStruct().isDifferent(s_SettingsStruct);
    ui->applyBtn->setEnabled(isDiff);
}

void SettingsDlg::on_rbFormat24H_clicked()
{
    s_SettingsStruct.m_FormatHourEnum = FormatHourEnum::FORMAT_24H;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbFormat12H_clicked()
{
    s_SettingsStruct.m_FormatHourEnum = FormatHourEnum::FORMAT_12H;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbUnitCelsius_clicked()
{
    s_SettingsStruct.m_TemperatureUnit = TemperatureUnitEnum::UNIT_CELSIUS;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbUnitFahrenheit_clicked()
{
    s_SettingsStruct.m_TemperatureUnit = TemperatureUnitEnum::UNIT_FAHRENHEIT;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbUnitKelvin_clicked()
{
    s_SettingsStruct.m_TemperatureUnit = TemperatureUnitEnum::UNIT_KELVIN;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_cbFontFamily_currentFontChanged(const QFont &vFont)
{
    s_SettingsStruct.m_FontFamily = vFont.family();
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_cbLanguage_activated(const QString &vLanguage)
{
    s_SettingsStruct.m_Language = vLanguage;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_sbDelay_valueChanged(const int& vRefreshDelayInMinutes)
{
    s_SettingsStruct.m_RefreshDelayInMinutes = vRefreshDelayInMinutes;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_edIP_textChanged(const QString &vIp)
{
    s_SettingsStruct.m_IP = vIp;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_edPort_textChanged(const QString &vPort)
{
    s_SettingsStruct.m_Port = vPort;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_edApiKey_textChanged(const QString &vApiKey)
{
    s_SettingsStruct.m_ApiKey = vApiKey;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_edCity_textChanged(const QString &vVille)
{
    s_SettingsStruct.m_Ville = vVille;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbStyleDay_clicked()
{
    s_SettingsStruct.m_Style = StyleEnum::STYLE_DAY;
    CheckIfSomethingWasChanged();
}

void SettingsDlg::on_rbStyleNight_clicked()
{
    s_SettingsStruct.m_Style = StyleEnum::STYLE_NIGHT;
    CheckIfSomethingWasChanged();
}
