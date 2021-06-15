#include "mainwindow.h"
#include <QApplication>
#include "balisevillepanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    BaliseVillePanel b;
    b.show();
    return a.exec();
}
