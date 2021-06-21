#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include "LangManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));

    LangManager::Instance()->Init();

    MainWindow w;
    w.show();

    return app.exec();
}
