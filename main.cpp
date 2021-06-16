#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    QTranslator myappTranslator;
    myappTranslator.load(QLocale(), QLatin1String("myapp"), QLatin1String("_"), QLatin1String(":/i18n"));
    app.installTranslator(&myappTranslator);

    return app.exec();
}
