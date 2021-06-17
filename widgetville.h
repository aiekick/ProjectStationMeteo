#ifndef WIDGETVILLE_H
#define WIDGETVILLE_H
#include "baliseVille.h"
#include <QWidget>
#include "GlobalSettings.h"
namespace Ui {
class widgetville;
}

class widgetville : public QWidget
{
    Q_OBJECT

public:
    explicit widgetville(QWidget *parent = nullptr);
    ~widgetville();





void remplissage(DatasMeteo);
private:
    Ui::widgetville *ui;
};

#endif // WIDGETVILLE_H
