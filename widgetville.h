#ifndef WIDGETVILLE_H
#define WIDGETVILLE_H

#include <QWidget>
#include "GlobalSettings.h"
#include "datasMeteo.h"

namespace Ui {
class WidgetVille;
}

class WidgetVille : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetVille(QWidget *parent = nullptr);
    ~WidgetVille();

    void remplissage(DatasMeteo);
    void changeEvent(QEvent *e) override;

    void ApplyStyle();

private:
    Ui::WidgetVille *ui;
};

#endif // WIDGETVILLE_H
