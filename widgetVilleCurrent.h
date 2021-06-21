#ifndef WIDGETVILLECURRENT_H
#define WIDGETVILLECURRENT_H

#include <QWidget>
#include "GlobalSettings.h"
#include "datasMeteo.h"

namespace Ui {
class WidgetVilleCurrent;
}

class WidgetVilleCurrent : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVilleCurrent(QWidget *parent = nullptr);
    ~WidgetVilleCurrent();

    void paintEvent(QPaintEvent *) override;
    void changeEvent(QEvent *e) override;

    void remplissage(DatasMeteo);

    void ApplyStyle();

private:
    Ui::WidgetVilleCurrent *ui;
};

#endif // WIDGETVILLECURRENT_H
