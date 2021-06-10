#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&m_Socket,SIGNAL(connected()),this,SLOT(onConnected()));
    connect(&m_Socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString ip_port = ui->lineEdit_IP_PORT->text();
    auto list = ip_port.split(":");
    if (list.size() == 2U)
    {
        const QString ip = list[0];
        bool isOk = false;
        const int port = list[1].toInt(&isOk);
        if (isOk)
        {
            m_Socket.connectToHost(QHostAddress(ip), port, QIODevice::ReadWrite);
        }
        else
        {
            ui->labelConnection->setText("Port is bad");
        }
    }
    else
    {
        ui->labelConnection->setText("the syntax is 'ip:port' => ex '127.0.0.1:4583'");
    }
}

void MainWindow::onConnected()
{
    ui->labelConnection->setText("Connected");
}

void MainWindow::onReadyRead()
{
    QString line;
    while(m_Socket.canReadLine())
    {
        line = m_Socket.readLine();
    }
    ui->plainTextEdit->setPlainText(line);
}

void MainWindow::on_pushButton_2_clicked()
{
    QTextStream textInput(&m_Socket);
    textInput << ui->lineEdit->text();
}

