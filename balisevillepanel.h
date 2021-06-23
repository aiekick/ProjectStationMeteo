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

    void updatedataville();
    void changeEvent(QEvent *e) override;

    void ApplyStyle();

private:
    Ui::BaliseVillePanel *ui;
    BaliseVille objville;
};

#endif // BALISEVILLEPANEL_H
