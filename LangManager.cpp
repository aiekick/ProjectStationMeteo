#include "LangManager.h"
#include "GlobalSettings.h"
#include <QApplication>
#include <QDir>

void LangManager::Init()
{
    // format systems language
    QString defaultLocale = QLocale::system().name(); // "fr_FR"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // "fr"

    /*auto m_langPath = QApplication::applicationDirPath();
    m_langPath.append("/lang");
    QDir dir(m_langPath);
    QStringList fileNames = dir.entryList(QStringList("*.qm"));

    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString lang;
        lang = fileNames[i]; // "station_meteo_fr.qm"
        lang.truncate(lang.lastIndexOf('.')); // "station_meteo_fr"
        lang.remove(0, lang.lastIndexOf('_') + 1); // "fr"
        lang = lang.toUpper(); // FR
        m_Translations[lang] = m_langPath + "/" + fileNames[i];
    }*/

    m_Translations["FR"] = ":/lang/station_meteo_fr.qm";
    m_Translations["EN"] = ":/lang/station_meteo_en.qm";

    const auto& lang = GlobalSettings::Instance()->getLanguage();
    ApplyLang(lang);
}

void LangManager::Unit()
{

}

void LangManager::ApplyLang(const QString& vLang)
{
    if (m_Translations.find(vLang) != m_Translations.end())
    {
        m_AppTranslator.load(m_Translations[vLang]);
        qApp->installTranslator(&m_AppTranslator);
    }
}

std::map<QString, QString> LangManager::getTranslations()
{
    return m_Translations;
}
