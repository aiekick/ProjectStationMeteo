#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFrame>

#include "balisevillepanel.h"
#include "baliseMerPanel.h"
#include "StyleManager.h"
#include "settingsdlg.h"
#include "aboutdialog.h"

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitMainWindow();
}

MainWindow::~MainWindow()
{
    UnitMainWindow();
    delete ui;
}

////////////////////////////////////////
/// PUBLIC
////////////////////////////////////////

void MainWindow::on_actionSettings_triggered()
{
    SettingsDlg _SettingsDlg(this);
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

////////////////////////////////////////
/// PRIVATE
////////////////////////////////////////

////////////////////////////////////////
/// \brief Init widgets and do some other inits actions
///
void MainWindow::InitMainWindow()
{
    StyleManager::Instance()->Init();

    m_MainLayout = new QVBoxLayout(ui->centralwidget);
    ui->centralwidget->setLayout(m_MainLayout);

    m_BaliseMerPanel = new BaliseMerPanel(this);
    m_MainLayout->addWidget(m_BaliseMerPanel);

    m_Separator = new QFrame(this);
    m_Separator->setFrameShape(QFrame::HLine);
    m_MainLayout->addWidget(m_Separator);

    m_BaliseVillePanel = new BaliseVillePanel(this);
    m_MainLayout->addWidget(m_BaliseVillePanel);
}

////////////////////////////////////////
/// \brief Unit widgets and do some others unit actions
///
void MainWindow::UnitMainWindow()
{
    delete m_BaliseVillePanel;
    delete m_MainLayout;

    StyleManager::Instance()->Unit();
}

////////////////////////////////////////
/// \brief Will upodate meteo datas and widgets
///
void MainWindow::UpdateMainWindow()
{

}
