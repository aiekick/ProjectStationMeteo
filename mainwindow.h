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

class ShaderWidget;
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

private slots:
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionRefresh_triggered();
    void on_timeout();
    void on_ApplySettingsChange();

private:
    Ui::MainWindow *ui = nullptr;
    BaliseVillePanel *m_BaliseVillePanel = nullptr;
    BaliseMerPanel *m_BaliseMerPanel = nullptr;
    ShaderWidget *m_ShaderWidget = nullptr;
    QVBoxLayout *m_MainLayout = nullptr;
    QFrame *m_Separator = nullptr;
    QTimer m_Timer;
};

#endif // MAINWINDOW_H
