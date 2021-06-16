#ifndef BALISEVILLEPANEL_H
#define BALISEVILLEPANEL_H
#include "baliseVille.h"
#include <QWidget>
#include "widgetville.h"
namespace Ui {
class BaliseVillePanel;
}

class BaliseVillePanel : public QWidget
{
    Q_OBJECT

public:
    explicit BaliseVillePanel(QWidget *parent = nullptr);
    ~BaliseVillePanel();

    widgetville widget;

private slots:
    void on_pushButtonville_clicked();



private:
    Ui::BaliseVillePanel *ui;
    BaliseVille objville;
    widgetville * jouractu;

};

#endif // BALISEVILLEPANEL_H
