#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class BaliseVillePanel;
class BaliseMerPanel;
class QVBoxLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui = nullptr;
    BaliseVillePanel *m_BaliseVillePanel = nullptr;
    BaliseMerPanel *m_BaliseMerPanel = nullptr;
    QVBoxLayout *m_MainLayout = nullptr;
};

#endif // MAINWINDOW_H
