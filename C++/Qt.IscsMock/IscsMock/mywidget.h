#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include "ui_mywidget.h"

class MyWidget : public QWidget
{
	Q_OBJECT

public:
	MyWidget(QWidget *parent = 0);
	~MyWidget();

protected:
	bool eventFilter(QObject *target, QEvent *e);

private:
	Ui::MyWidget ui;
};

#endif // MYWIDGET_H
