#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QTimer>

#include "GlobalSettings.h"
#include "balisevillepanel.h"
#include "baliseMerPanel.h"
#include "settingsdlg.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GlobalSettings::Instance()->LoadConfigFile();

    m_Timer.setParent(this);
    connect(&m_Timer, SIGNAL(timeout()), this, SLOT(on_timeout()));

    UpdateTimer();
    UpdateMainWindow();
}

MainWindow::~MainWindow()
{
    GlobalSettings::Instance()->SaveConfigFile();

    delete ui;
}

////////////////////////////////////////
/// EVENTS
////////////////////////////////////////

void MainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
   }
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
    UpdateMainWindow();
}

////////////////////////////////////////
/// PRIVATE
////////////////////////////////////////

////////////////////////////////////////
/// \brief Will update meteo datas and widgets
///
void MainWindow::UpdateMainWindow()
{
    ui->baliseMerPanel->updateData();
    ui->baliseVillePanel->updatedataville();
}

void MainWindow::UpdateTimer()
{
    const auto _delayMs = 1000 * 60 * GlobalSettings::Instance()->getRefreshDelayInMinutes();
    m_Timer.start(_delayMs);
}
