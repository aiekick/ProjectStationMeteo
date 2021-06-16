#include "GlobalSettings.h"

/////////////////////////////////////////////
/// LOAD / SAVE
/////////////////////////////////////////////

void GlobalSettings::LoadConfigFile(const QString& vFilePathName)
{

}

void GlobalSettings::SaveConfigFile(const QString& vFilePathName)
{

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

const QString& GlobalSettings::getStyle() const
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

void GlobalSettings::setStyle(const QString& vStyle)
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

void GlobalSettings::setSettingsStruct(const SettingsStruct& vSettingsStruct)
{
    m_SettingsStruct = vSettingsStruct;
}

