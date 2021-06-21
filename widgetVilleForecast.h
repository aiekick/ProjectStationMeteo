#ifndef WIDGETVILLEFORECAST_H
#define WIDGETVILLEFORECAST_H

#include <QWidget>
#include "GlobalSettings.h"
#include "datasMeteo.h"

namespace Ui {
class WidgetVilleForecast;
}

class WidgetVilleForecast : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVilleForecast(QWidget *parent = nullptr);
    ~WidgetVilleForecast();

    void paintEvent(QPaintEvent *) override;
    void changeEvent(QEvent *e) override;

    void remplissage(DatasMeteo);

    void ApplyStyle();

private:
    Ui::WidgetVilleForecast *ui;
};

#endif // WIDGETVILLEFORECAST_H
