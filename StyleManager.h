#pragma once

#include <QMap>
#include <QString>

class StyleManager
{
public:
    QMap<QString, QString> m_Styles;

public:
    void ScanForStyles(const QString& vSearchDirectory);
    void ApplyStyle(const QString& vStyleToApply);

public:
    static StyleManager* Instance()
    {
        static StyleManager _instance;
        return &_instance;
    }

protected:
    StyleManager() = default;
    ~StyleManager() = default;
    StyleManager(const StyleManager&) = delete;
    StyleManager& operator =(const StyleManager&) = delete;
};
