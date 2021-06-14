#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "balise.h"
#include "baliseMer.h"

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_Test_clicked()
{
    this->ui->label_Test->setText("OK");
}
