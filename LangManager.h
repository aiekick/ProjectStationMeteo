#pragma once

#include <map>
#include <QString>
#include <QTranslator>

class LangManager
{
private:
    QTranslator m_AppTranslator;
    std::map<QString, QString> m_Translations;

public:
    void Init();
    void Unit();

    void ApplyLang(const QString& vLang);
    std::map<QString, QString> getTranslations();

public:
    static LangManager* Instance()
    {
        static LangManager _instance;
        return &_instance;
    }

protected:
    LangManager() = default;
    ~LangManager() = default;
    LangManager(const LangManager&) = delete;
    LangManager& operator =(const LangManager&) = delete;
};
