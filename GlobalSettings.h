#pragma once

#include <QString>
#include <QVector>

enum class FormatHourEnum
{
    FORMAT_12H = 0,
    FORMAT_24H
};

enum class TemperatureUnitEnum
{
    UNIT_CELSIUS=0,
    UNIT_FAHRENHEIT,
    UNIT_KELVIN
};

class GlobalSettings
{
public:
    struct SettingsStruct
    {
        FormatHourEnum m_FormatHourEnum = FormatHourEnum::FORMAT_24H;
        TemperatureUnitEnum m_TemperatureUnit = TemperatureUnitEnum::UNIT_CELSIUS;
        QString m_Ville = "Paris";
        QString m_FontFamily = "Arial";
        QString m_ApiKey = "58e08b52cadfc9c96fc8354666cec712";
        QString m_IP = "82.65.244.166";
        QString m_Port = "48001";
        QString m_Language = "fr";
        QString m_Style = "Default";

        bool isDifferent(const SettingsStruct& vSettingsStruct) const
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
            return false;
        }
    };

private:
     SettingsStruct m_SettingsStruct;

public:
    void LoadConfigFile(const QString& vFilePathName);
    void SaveConfigFile(const QString& vFilePathName);

    const FormatHourEnum& getFormatHourEnum() const;
    const TemperatureUnitEnum& getTemperatureUnit() const;
    const QString& getFontFamily() const;
    const QString& getStyle() const;
    const QString& getLanguage() const;
    const QString& getApiKey() const;
    const QString& getVille() const;
    const QString& getIP() const;
    const QString& getPort() const;
    const SettingsStruct& getSettingsStruct() const;

    void setFormatHourEnum(const FormatHourEnum& vFormatHourEnum);
    void setTemperatureUnit(const TemperatureUnitEnum& vTemperatureUnit);
    void setFontFamily(const QString &vFontFamily);
    void setStyle(const QString &vStyle);
    void setLanguage(const QString &vLanguage);
    void setApiKey(const QString &vApiKey);
    void setVille(const QString &vVille);
    void setIP(const QString &vIP);
    void setPort(const QString &vPort);
    void setSettingsStruct(const SettingsStruct& vSettingsStruct);

public:
    static GlobalSettings* Instance()
    {
        static GlobalSettings _instance;
        return &_instance;
    }

protected:
    GlobalSettings() = default;
    ~GlobalSettings() = default;
    GlobalSettings(const GlobalSettings&) = delete;
    GlobalSettings& operator =(const GlobalSettings&) = delete;
};
