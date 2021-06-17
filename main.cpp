#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <qlocale.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QLocale::setDefault(QLocale("fr_FR"));

    QTranslator myappTranslator;
    //myappTranslator.load(QLocale(), QLatin1String("myapp"), QLatin1String("_"), QLatin1String(":/i18n"));
    myappTranslator.load("station_meteo_en");
    app.installTranslator(&myappTranslator);

    MainWindow w;
    w.show();

    return app.exec();
}
