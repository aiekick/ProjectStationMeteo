#include "mainwindow.h"
#include <QApplication>
#include "LangManager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LangManager::Instance()->Init();

    MainWindow w;
    w.show();

    return app.exec();
}
