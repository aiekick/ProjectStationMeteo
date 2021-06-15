#ifndef BALISEVILLEPANEL_H
#define BALISEVILLEPANEL_H
#include "baliseVille.h"
#include <QWidget>

namespace Ui {
class BaliseVillePanel;
}

class BaliseVillePanel : public QWidget
{
    Q_OBJECT

public:
    explicit BaliseVillePanel(QWidget *parent = nullptr);
    ~BaliseVillePanel();

private slots:
    void on_pushButtonville_clicked();

private:
    Ui::BaliseVillePanel *ui;
    BaliseVille objville;
};

#endif // BALISEVILLEPANEL_H
