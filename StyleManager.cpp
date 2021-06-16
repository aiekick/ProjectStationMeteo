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
        QFileInfo fi(file);
        auto name = fi.completeBaseName();
        auto path = fi.absoluteFilePath();

        if (m_Styles.find(name) == m_Styles.end())
        {
            m_Styles[name] = path;
        }
    }
}

void StyleManager::ApplyStyle(const QString& vStyleToApply)
{

}

const std::map<QString, QString>& StyleManager::getStyles()
{
    return m_Styles;
}
