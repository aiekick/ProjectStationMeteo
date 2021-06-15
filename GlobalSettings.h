#pragma once

#include <QString>
#include <QVector>

enum class HourFormatEnum
{
    FORMAT_12H = 0,
    FORMAT_24H
};

enum class TemperatureUnitEnum
{
    UNIT_CELSIUS=0,
    UNIT_FAHRENHEIT
};

class GlobalSettings
{
private:
    HourFormatEnum m_HourFormatEnum = HourFormatEnum::FORMAT_12H;
    TemperatureUnitEnum m_TemperatureUnit = TemperatureUnitEnum::UNIT_CELSIUS;
    QString m_Ville = "Paris";
    QString m_FontFamily = "Arial";
    QVector<QString> m_Styles;

public:
    void LoadConfigFile(const QString& vFilePathName);
    void SaveConfigFile(const QString& vFilePathName);

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
