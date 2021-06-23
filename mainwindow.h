#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "settingsdlg.h"
#include "aboutdialog.h"

//#define USE_STYLE_DOCK_PANE

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class QFrame;
class QVBoxLayout;
class BaliseMerPanel;
class BaliseVillePanel;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void UpdateMainWindow();
    void UpdateTimer();
    void UpdateDateTime();

    void changeEvent(QEvent *e) override;
    void ApplyStyle();

private slots:
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionRefresh_triggered();
    void on_DateTimer_Timeout();
    void on_RefreshTimer_Timeout();
    void on_ApplySettingsChange();

#ifdef USE_STYLE_DOCK_PANE
    void on_openDayStyle_clicked();
    void on_saveDayStyle_clicked();
    void on_openNightStyle_clicked();
    void on_saveNightStyle_clicked();
    void on_applyBtn_clicked();
#endif

private:
    Ui::MainWindow *ui = nullptr;
    QTimer m_DateTimer;
    QTimer m_RefreshTimer;
};

#endif // MAINWINDOW_H
