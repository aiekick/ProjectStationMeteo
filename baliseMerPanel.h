#ifndef BALISEMERPANEL_H
#define BALISEMERPANEL_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class baliseMerPanel; }
QT_END_NAMESPACE

class baliseMerPanel : public QMainWindow
{
	Q_OBJECT

public:
	baliseMerPanel(QWidget *parent = nullptr);
	~baliseMerPanel();
	void updateData();

private slots:
    void on_pushButton_Refresh_clicked();

    void on_pushButton_Degrees_clicked();

private:
	Ui::baliseMerPanel *ui;
};


#endif
