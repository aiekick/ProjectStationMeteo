#pragma once

#include <map>
#include <QString>
#include <QTranslator>

class LangManager
{
private:
    std::map<QString, QString> m_Translations;
    QTranslator appTranslator;

public:
    void Init();
    void Unit();

    void ApplyLang(const QString& vLang);
    void ReApplyCurrent();
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
