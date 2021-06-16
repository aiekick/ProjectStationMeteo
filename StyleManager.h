#pragma once

#include <map>
#include <QString>

class StyleManager
{
public:
    std::map<QString, QString> m_Styles;

public:
    bool Init();
    void Unit();
    void ScanForStyles(const QString& vSearchDirectory);
    void ApplyStyle(const QString& vStyleToApply);

    const std::map<QString, QString>& getStyles();

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
