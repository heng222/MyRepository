#include "StdAfx.h"
#include "mywidget.h"
#include <QMessageBox> 
#include <QMainWindow>

MyWidget::MyWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
}

MyWidget::~MyWidget()
{

}

bool MyWidget::eventFilter(QObject *target, QEvent *e)
{
	if(target == ui.pushButton)
	{
		if(e->type() == QEvent::MouseButtonPress)
			QMessageBox::about(this,"x","x");
	}

	return QWidget::eventFilter(target, e);
}
