#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

    void changeEvent(QEvent *e) override;

    void ApplyStyle();

private slots:
    void on_closeBtn_clicked();

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
