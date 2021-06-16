#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void InitMainWindow();
    void UnitMainWindow();
    void UpdateMainWindow();

private slots:
    void on_actionSettings_triggered();
    void on_actionAbout_triggered();
    void on_actionRefresh_triggered();

private:
    Ui::MainWindow *ui = nullptr;
    BaliseVillePanel *m_BaliseVillePanel = nullptr;
    BaliseMerPanel *m_BaliseMerPanel = nullptr;
    QVBoxLayout *m_MainLayout = nullptr;
    QFrame *m_Separator = nullptr;
};

#endif // MAINWINDOW_H
