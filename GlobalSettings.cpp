#include "GlobalSettings.h"
#include <QSettings>
#include <QFileInfo>
#include <QApplication>

/////////////////////////////////////////////
/////////////////////////////////////////////

#define CONFIG_FILE_PATH_NAME "config.ini"

/////////////////////////////////////////////
/// SettingsStruct
/////////////////////////////////////////////

bool GlobalSettings::SettingsStruct::isDifferent(const SettingsStruct& vSettingsStruct) const
{
    if (m_FormatHourEnum != vSettingsStruct.m_FormatHourEnum) return true;
    if (m_TemperatureUnit != vSettingsStruct.m_TemperatureUnit) return true;
    if (m_Ville != vSettingsStruct.m_Ville) return true;
    if (m_FontFamily != vSettingsStruct.m_FontFamily) return true;
    if (m_ApiKey != vSettingsStruct.m_ApiKey) return true;
    if (m_IP != vSettingsStruct.m_IP) return true;
    if (m_Port != vSettingsStruct.m_Port) return true;
    if (m_Language != vSettingsStruct.m_Language) return true;
    if (m_Style != vSettingsStruct.m_Style) return true;
    if (m_RefreshDelayInMinutes != vSettingsStruct.m_RefreshDelayInMinutes) return true;
    return false;
}

void GlobalSettings::SettingsStruct::Load(const QString& vFilePathName)
{
    GlobalSettings::SettingsStruct _default;

    QSettings config(vFilePathName, QSettings::IniFormat);

    m_FormatHourEnum = (FormatHourEnum)config.value("FormatHourEnum", (int)_default.m_FormatHourEnum).toInt();
    m_TemperatureUnit = (TemperatureUnitEnum)config.value("TemperatureUnit", (int)_default.m_TemperatureUnit).toInt();
    m_Ville = config.value("Ville", _default.m_Ville).toString();
    m_FontFamily = config.value("FontFamily", _default.m_FontFamily).toString();
    m_ApiKey = config.value("ApiKey", _default.m_ApiKey).toString();
    m_IP = config.value("IP", _default.m_IP).toString();
    m_Port = config.value("Port", _default.m_Port).toString();
    m_Language = config.value("Language", _default.m_Language).toString();
    m_Style = (StyleEnum)config.value("Style", (int)_default.m_Style).toInt();
    m_RefreshDelayInMinutes = config.value("RefreshDelayInMinutes", _default.m_RefreshDelayInMinutes).toUInt();
}

void GlobalSettings::SettingsStruct::Save(const QString& vFilePathName)
{
    QSettings config(vFilePathName, QSettings::IniFormat);

    config.setValue("FormatHourEnum", (int)m_FormatHourEnum);
    config.setValue("TemperatureUnit", (int)m_TemperatureUnit);
    config.setValue("Ville", m_Ville);
    config.setValue("FontFamily", m_FontFamily);
    config.setValue("ApiKey", m_ApiKey);
    config.setValue("IP", m_IP);
    config.setValue("Port", m_Port);
    config.setValue("Language", m_Language);
    config.setValue("Style", (int)m_Style);
    config.setValue("RefreshDelayInMinutes", m_RefreshDelayInMinutes);

    config.sync();
}

/////////////////////////////////////////////
/// LOAD / SAVE
/////////////////////////////////////////////

void GlobalSettings::LoadConfigFile()
{
    if (QFileInfo::exists(CONFIG_FILE_PATH_NAME))
    {
        m_SettingsStruct.Load(CONFIG_FILE_PATH_NAME);
    }

    ApplyStyle(m_SettingsStruct.m_Style);
}

void GlobalSettings::SaveConfigFile()
{
    m_SettingsStruct.Save(CONFIG_FILE_PATH_NAME);
}

/////////////////////////////////////////////
/// GETTERS
/////////////////////////////////////////////

const FormatHourEnum& GlobalSettings::getFormatHourEnum() const
{
    return m_SettingsStruct.m_FormatHourEnum;
}

const TemperatureUnitEnum& GlobalSettings::getTemperatureUnit() const
{
    return m_SettingsStruct.m_TemperatureUnit;
}

const QString& GlobalSettings::getFontFamily() const
{
    return m_SettingsStruct.m_FontFamily;
}

const StyleEnum& GlobalSettings::getStyle() const
{
    return m_SettingsStruct.m_Style;
}

const QString& GlobalSettings::getLanguage() const
{
    return m_SettingsStruct.m_Language;
}

const QString& GlobalSettings::getApiKey() const
{
    return m_SettingsStruct.m_ApiKey;
}

const QString& GlobalSettings::getVille() const
{
    return m_SettingsStruct.m_Ville;
}

const QString& GlobalSettings::getIP() const
{
    return m_SettingsStruct.m_IP;
}

const QString& GlobalSettings::getPort() const
{
    return m_SettingsStruct.m_Port;
}

const uint32_t GlobalSettings::getRefreshDelayInMinutes() const
{
    return m_SettingsStruct.m_RefreshDelayInMinutes;
}

const GlobalSettings::SettingsStruct& GlobalSettings::getSettingsStruct() const
{
    return m_SettingsStruct;
}

/////////////////////////////////////////////
/// SETTERS
/////////////////////////////////////////////

void GlobalSettings::setFormatHourEnum(const FormatHourEnum& vFormatHourEnum)
{
    m_SettingsStruct.m_FormatHourEnum = vFormatHourEnum;
}

void GlobalSettings::setTemperatureUnit(const TemperatureUnitEnum& vTemperatureUnitEnum)
{
    m_SettingsStruct.m_TemperatureUnit = vTemperatureUnitEnum;
}

void GlobalSettings::setFontFamily(const QString& vFontFamily)
{
    m_SettingsStruct.m_FontFamily = vFontFamily;
}

void GlobalSettings::setStyle(const StyleEnum& vStyle)
{
    m_SettingsStruct.m_Style = vStyle;
}

void GlobalSettings::setLanguage(const QString& vLanguage)
{
    m_SettingsStruct.m_Language = vLanguage;
}

void GlobalSettings::setApiKey(const QString& vApiKey)
{
    m_SettingsStruct.m_ApiKey = vApiKey;
}

void GlobalSettings::setVille(const QString& vVille)
{
    m_SettingsStruct.m_Ville = vVille;
}

void GlobalSettings::setIP(const QString& vIP)
{
    m_SettingsStruct.m_IP = vIP;
}

void GlobalSettings::setPort(const QString& vPort)
{
    m_SettingsStruct.m_Port = vPort;
}

void GlobalSettings::setRefreshDelayInMinutes(const uint32_t vRefreshDelayInMinutes)
{
    m_SettingsStruct.m_RefreshDelayInMinutes = vRefreshDelayInMinutes;
}

void GlobalSettings::setSettingsStruct(const SettingsStruct& vSettingsStruct)
{
    m_SettingsStruct = vSettingsStruct;
}

/////////////////////////////////////////////
/// APPLY
/////////////////////////////////////////////

void GlobalSettings::ApplyStyle(const StyleEnum& vStyleToApply)
{
    QString filePathStr;
    if (vStyleToApply == StyleEnum::STYLE_DAY)
    {
        filePathStr = "";//":/styles/baseDay.qss";
    }
    else if (vStyleToApply == StyleEnum::STYLE_NIGHT)
    {
        filePathStr = ":/styles/baseNight.qss";
    }

    if (!filePathStr.isEmpty())
    {
        QFile fp(filePathStr);
        if (fp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const auto& fc = fp.readAll();
            qApp->setStyleSheet(fc);
            fp.close();
        }
    }
    else
    {
       qApp->setStyleSheet("");
    }
}

/////////////////////////////////////////////
/// THEME
/////////////////////////////////////////////

QString GlobalSettings::GetThemeIconPath(const QString& vIconName)
{
    QString res = ":/theme/icons/";

    switch (m_SettingsStruct.m_Style)
    {
    case StyleEnum::STYLE_DAY:
        res += "White_bg";
        break;
    case StyleEnum::STYLE_NIGHT:
        res += "Black_bg";
        break;
    }

    res += "/" + vIconName + ".png";

    return res;
}
