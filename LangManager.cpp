#include "LangManager.h"
#include "GlobalSettings.h"
#include <QApplication>
#include <QDir>
#include <QDebug>

void LangManager::Init()
{
    // format systems language
    QString defaultLocale = QLocale::system().name(); // "fr_FR"
    defaultLocale.truncate(defaultLocale.lastIndexOf('_')); // "fr"

    QDir dir(":/translations");
    QStringList fileNames = dir.entryList(QStringList("*.qm"));

    for (int i = 0; i < fileNames.size(); ++i)
    {
        QString lang;
        lang = fileNames[i]; // "station_meteo_fr.qm"
        lang.truncate(lang.lastIndexOf('.')); // "station_meteo_fr"
        lang.remove(0, lang.lastIndexOf('_') + 1); // "fr"
        lang = lang.toUpper(); // FR
        m_Translations[lang] = ":/translations/" + fileNames[i];
    }

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
        QTranslator appTranslator;
        if (appTranslator.load(m_Translations[vLang]))
        {
            if (!qApp->installTranslator(&appTranslator))
            {
                qDebug() << "Fail to install translation";
            }
        }
        else
        {
            qDebug() << "Fail to load translation";
        }
    }
}

std::map<QString, QString> LangManager::getTranslations()
{
    return m_Translations;
}
