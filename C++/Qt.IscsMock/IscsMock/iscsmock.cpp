#include "stdafx.h"
#include "iscsmock.h"
#include <QMessageBox> 
#include <QMainWindow>
#include "mywidget.h"

QApplication*  app;

IscsMock::IscsMock()
{
	int k=0;
	app = new QApplication(k, NULL);

	m_pMywidget = new MyWidget();
	
}

IscsMock::~IscsMock()
{
	delete m_pMywidget;
	app->exit();
}


long IscsMock::GetWindows() 
{
	WId id = m_pMywidget->winId();

	QString tip ;//QString("m_pMywidget->winId = %1¡£", id);
	tip.sprintf("m_pMywidget->winId = %d", id);
	
	QMessageBox::about(NULL, "Hi", tip);

	return (long)(id);
}


void IscsMock::ShowWindow(long parent)
{
	//m_pMywidget = new MyWidget((QWidget*)parent);
	m_pMywidget->move(0,0);
	m_pMywidget->show();
}