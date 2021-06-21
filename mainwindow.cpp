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

    ui->retranslateUi(this);

    m_DateTimer.setParent(this);
    connect(&m_DateTimer, SIGNAL(timeout()), this, SLOT(on_DateTimer_Timeout()));
    m_DateTimer.start(1000); // on refresh per sec

    m_RefreshTimer.setParent(this);
    connect(&m_RefreshTimer, SIGNAL(timeout()), this, SLOT(on_RefreshTimer_Timeout()));

    ApplyStyle();
    UpdateTimer();
    UpdateMainWindow();
}

MainWindow::~MainWindow()
{
    GlobalSettings::Instance()->SaveConfigFile();

    delete ui;
}

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

void MainWindow::ApplyStyle()
{
    if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_DAY)
    {

        //filePathStr = "";//":/styles/baseDay.qss";
    }
    else if (GlobalSettings::Instance()->getStyle() == StyleEnum::STYLE_NIGHT)
    {
        //filePathStr = ":/styles/baseNight.qss";
        //QPalette pal= QApplication::palette();
        //pal.setColor(QPalette::Window, QColor(4,7,13));
        //pal.setColor(QPalette::Button, QColor(Qt::blue));
        //pal.setColor(QPalette::ButtonText, QColor(Qt::yellow));
        //pal.setBrush(QPalette::WindowText, QBrush(QColor(Qt::yellow)));
        //pal.setColor(QPalette::Highlight, QColor(Qt::green));
        //QApplication::setPalette(pal);
    }

    ui->baliseMerPanel->ApplyStyle();
    ui->baliseVillePanel->ApplyStyle();
}

////////////////////////////////////////
/// SLOTS
////////////////////////////////////////

void MainWindow::on_actionSettings_triggered()
{
    auto _SettingsDlg = new SettingsDlg();
    _SettingsDlg->ApplyStyle();
    connect(_SettingsDlg, SIGNAL(ApplySettingsChange()), this, SLOT(on_ApplySettingsChange()));
    _SettingsDlg->open();
    //_SettingsDlg->deleteLater();
}

void MainWindow::on_actionAbout_triggered()
{
    auto _AboutDialog = new AboutDialog();
    _AboutDialog->ApplyStyle();
    _AboutDialog->open();
    //_AboutDialog->deleteLater();
}

void MainWindow::on_actionRefresh_triggered()
{
    UpdateMainWindow();
}

void MainWindow::on_DateTimer_Timeout()
{
    UpdateDateTime();
}

void MainWindow::on_RefreshTimer_Timeout()
{
    UpdateMainWindow();
}

void MainWindow::on_ApplySettingsChange()
{
    UpdateDateTime();
    UpdateTimer();
    UpdateMainWindow();
    ApplyStyle();
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
    m_RefreshTimer.start(_delayMs);
}

void MainWindow::UpdateDateTime()
{
    switch(GlobalSettings::Instance()->getFormatHourEnum())
    {
    case FormatHourEnum::FORMAT_12H:
        ui->labelDate->setText(QLocale("en_EN").toString(QDateTime::currentDateTime(), "dd.MM.yyyy - HH:mm:ss a"));
        break;
    case FormatHourEnum::FORMAT_24H:
        ui->labelDate->setText(QDateTime::currentDateTime().toString("dd.MM.yyyy - HH:mm:ss"));
        break;
    }
}

////////////////////////////////////////
/// STYLE DOCK PANE
////////////////////////////////////////

#ifdef USE_STYLE_DOCK_PANE

void MainWindow::on_openDayStyle_clicked()
{
    QString filePathStr = "baseDay.qss";

    if (!filePathStr.isEmpty())
    {
        QFile fp(filePathStr);
        if (fp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const auto& fc = fp.readAll();
            ui->plainTextEditStyle->setPlainText(fc);
            GlobalSettings::Instance()->setStyle(StyleEnum::STYLE_DAY);
            ApplyStyle();
            qApp->setStyleSheet(fc);
            fp.close();
        }
    }
}

void MainWindow::on_saveDayStyle_clicked()
{
    const auto& fc = ui->plainTextEditStyle->toPlainText();
    if (!fc.isEmpty())
    {
        QString filePathStr = "baseDay.qss";
        if (!filePathStr.isEmpty())
        {
            QFile fp(filePathStr);
            if (fp.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                fp.write(fc.toLatin1());
                fp.close();
            }
        }
    }
}

void MainWindow::on_openNightStyle_clicked()
{
    QString filePathStr = "baseNight.qss";

    if (!filePathStr.isEmpty())
    {
        QFile fp(filePathStr);
        if (fp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            const auto& fc = fp.readAll();
            ui->plainTextEditStyle->setPlainText(fc);
            GlobalSettings::Instance()->setStyle(StyleEnum::STYLE_NIGHT);
            ApplyStyle();
            qApp->setStyleSheet(fc);
            fp.close();
        }
    }
}

void MainWindow::on_saveNightStyle_clicked()
{
    const auto& fc = ui->plainTextEditStyle->toPlainText();
    if (!fc.isEmpty())
    {
        QString filePathStr = "baseNight.qss";
        if (!filePathStr.isEmpty())
        {
            QFile fp(filePathStr);
            if (fp.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                const auto& fc = ui->plainTextEditStyle->toPlainText();
                fp.write(fc.toLatin1());
                fp.close();
            }
        }
    }
}

void MainWindow::on_applyBtn_clicked()
{
    auto plainText = ui->plainTextEditStyle->toPlainText();
    qApp->setStyleSheet(plainText);
}

#endif

