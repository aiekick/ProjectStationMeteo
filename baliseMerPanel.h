#ifndef BALISEMERPANEL_H
#define BALISEMERPANEL_H

#include <QWidget>
#include "baliseMer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class baliseMerPanel; }
QT_END_NAMESPACE

class BaliseMerPanel : public QWidget
{
	Q_OBJECT

public:
    BaliseMerPanel(QWidget *parent = nullptr);
    ~BaliseMerPanel();
	void updateData(); //Print data to the panel


private slots:
    void on_pushButton_Refresh_clicked();


    void on_pushButton_See_Graph_Details_clicked();

private:
	Ui::baliseMerPanel *ui;
	BaliseMer baliseMer; 

};

#endif
