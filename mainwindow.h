#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

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

    void changeEvent(QEvent *e) override;

private slots:
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionRefresh_triggered();
    void on_timeout();
    void on_ApplySettingsChange();

private:
    Ui::MainWindow *ui = nullptr;
    QTimer m_Timer;
};

#endif // MAINWINDOW_H
