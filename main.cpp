#include "mainwindow.h"
#include "baliseMerPanel.h"
#include <QApplication>

#include "balise.h"
#include "baliseMer.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
 
    baliseMerPanel x;
    x.show();
    


    return a.exec();
}