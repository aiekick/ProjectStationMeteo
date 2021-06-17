#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QTimer>

#include "GlobalSettings.h"
#include "balisevillepanel.h"
#include "baliseMerPanel.h"
#include "StyleManager.h"
#include "settingsdlg.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StyleManager::Instance()->Init();
    GlobalSettings::Instance()->LoadConfigFile();

    m_MainLayout = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(m_MainLayout);

    m_BaliseMerPanel = new BaliseMerPanel(this);
    m_MainLayout->addWidget(m_BaliseMerPanel);

    m_Separator = new QFrame(this);
    m_Separator->setFrameShape(QFrame::HLine);
    m_MainLayout->addWidget(m_Separator);

    m_BaliseVillePanel = new BaliseVillePanel(this);
    m_MainLayout->addWidget(m_BaliseVillePanel);

    m_Timer = new QTimer(this);
    connect(m_Timer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    UpdateTimer();
    UpdateMainWindow();
}

MainWindow::~MainWindow()
{
    delete m_Timer;
    delete m_BaliseVillePanel;
    delete m_Separator;
    delete m_BaliseMerPanel;
    delete m_MainLayout;

    GlobalSettings::Instance()->SaveConfigFile();
    StyleManager::Instance()->Unit();

    delete ui;
}

////////////////////////////////////////
/// SLOTS
////////////////////////////////////////

void MainWindow::on_actionSettings_triggered()
{
    SettingsDlg _SettingsDlg(this);
    connect(&_SettingsDlg, SIGNAL(ApplySettingsChange()), this, SLOT(on_ApplySettingsChange()));
    _SettingsDlg.setModal(true);
    _SettingsDlg.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog _AboutDialog(this);
    _AboutDialog.setModal(true);
    _AboutDialog.exec();
}

void MainWindow::on_actionRefresh_triggered()
{
    UpdateMainWindow();
}

void MainWindow::on_timeout()
{
    UpdateMainWindow();
}

void MainWindow::on_ApplySettingsChange()
{
    UpdateTimer();
}

////////////////////////////////////////
/// PRIVATE
////////////////////////////////////////

////////////////////////////////////////
/// \brief Will update meteo datas and widgets
///
void MainWindow::UpdateMainWindow()
{
    m_BaliseMerPanel->updateData();
}

void MainWindow::UpdateTimer()
{
    const auto _delayMs = 1000 * 60 * GlobalSettings::Instance()->getRefreshDelayInMinutes();
    m_Timer->setInterval(_delayMs);
    m_Timer->start();
}
