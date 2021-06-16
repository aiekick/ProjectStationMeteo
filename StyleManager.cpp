#include "StyleManager.h"
#include <QApplication>
#include <QDir>

bool StyleManager::Init()
{
    auto searchPath = qApp->applicationDirPath() + "/styles";
    ScanForStyles(searchPath);

    return true;
}

void StyleManager::Unit()
{
    m_Styles.clear();
}

void StyleManager::ScanForStyles(const QString& vSearchDirectory)
{
    QDir directory(vSearchDirectory);
    auto files = directory.entryList(QStringList() << "*.qss" << "*.QSS", QDir::Files);
    foreach(const auto& file, files)
    {
        auto name = QFileInfo(file).completeBaseName();

        if (m_Styles.find(name) == m_Styles.end())
        {
            m_Styles[name] = vSearchDirectory + "/" + file;
        }
    }
}

void StyleManager::ApplyStyle(const QString& vStyleToApply)
{
    if (!vStyleToApply.isEmpty())
    {
        if (vStyleToApply == "Default")
        {
            qApp->setStyleSheet("");
        }
        else
        {
            if (m_Styles.find(vStyleToApply) != m_Styles.end())
            {
                auto pathToLoad = m_Styles[vStyleToApply];
                if (!pathToLoad.isEmpty())
                {
                    QFile fp(pathToLoad);
                    if (fp.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::ExistingOnly))
                    {
                        const auto& fc = fp.readAll();
                        qApp->setStyleSheet(fc);

                        fp.close();
                    }
                }
            }
        }
    }
}

const std::map<QString, QString>& StyleManager::getStyles()
{
    return m_Styles;
}
