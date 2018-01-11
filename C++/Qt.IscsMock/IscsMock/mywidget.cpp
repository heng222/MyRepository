#include "StdAfx.h"
#include "mywidget.h"
#include <QMessageBox> 
#include <QMainWindow>

MyWidget::MyWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowFlags(Qt::Window);
}

MyWidget::~MyWidget()
{

}
