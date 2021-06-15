#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "balisevillepanel.h"
#include "baliseMerPanel.h"
#include "settingsdlg.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_MainLayout = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(m_MainLayout);

    m_BaliseMerPanel = new BaliseMerPanel(this);
    m_MainLayout->addWidget(m_BaliseMerPanel);

    m_BaliseVillePanel = new BaliseVillePanel(this);
    m_MainLayout->addWidget(m_BaliseVillePanel);
}

MainWindow::~MainWindow()
{
    delete m_BaliseVillePanel;
    delete m_MainLayout;
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDlg _SettingsDlg;
    _SettingsDlg.setModal(true);
    _SettingsDlg.exec();
}

