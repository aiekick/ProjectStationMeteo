#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "balise.h"
#include "baliseMer.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDebug>
#include <QJsonValue>

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Fenetre principale");
}

MainWindow::~MainWindow()
{
    delete ui;
}