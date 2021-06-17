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
    UNIT_CELSIUS = 0,
    UNIT_FAHRENHEIT,
    UNIT_KELVIN
};

class GlobalSettings
{
public:
    struct SettingsStruct
    {
        FormatHourEnum m_FormatHourEnum = FormatHourEnum::FORMAT_12H;
        TemperatureUnitEnum m_TemperatureUnit = TemperatureUnitEnum::UNIT_CELSIUS;
        QString m_Ville = "Paris";
        QString m_FontFamily = "Arial";
        QString m_ApiKey = "58e08b52cadfc9c96fc8354666cec712";
        QString m_IP = "82.65.244.166";
        QString m_Port = "48001";
        QString m_Language = "fr";
        QString m_Style = "Default";
        int m_RefreshDelayInMinutes = 10;

        bool isDifferent(const SettingsStruct& vSettingsStruct) const;
        void Load(const QString& vFilePathName);
        void Save(const QString& vFilePathName);
    };

private:
     SettingsStruct m_SettingsStruct;

public:
    void LoadConfigFile();
    void SaveConfigFile();

    const FormatHourEnum& getFormatHourEnum() const;
    const TemperatureUnitEnum& getTemperatureUnit() const;
    const QString& getFontFamily() const;
    const QString& getStyle() const;
    const QString& getLanguage() const;
    const QString& getApiKey() const;
    const QString& getVille() const;
    const QString& getIP() const;
    const QString& getPort() const;
    const uint32_t getRefreshDelayInMinutes() const;
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
    void setRefreshDelayInMinutes(const uint32_t vRefreshDelayInSeconds);
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
