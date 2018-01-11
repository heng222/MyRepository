#include "stdafx.h"
#include "iscsmock.h"
#include "QDateTimeEdit"
#include <QMessageBox> 
#include <QMainWindow>
#include "mywidget.h"
#include "qdatetimeedit.h"
#include <QMacNativeWidget>

QApplication*  app;

IscsMock::IscsMock()
{
	int k=0;
	app = new QApplication(k, NULL);
}

IscsMock::~IscsMock()
{
	delete m_pMywidget;
	//app->exit();
}

void IscsMock::Open(WId parentWnd)
{
	m_wndParent = parentWnd;
	QWidget *pParent=QWidget::find(m_wndParent);

	if (pParent == NULL)
	{
		QString tip ;
		tip.sprintf("pParent == NULL");	
		QMessageBox::about(NULL, "Hi", tip);
	}

	m_pMywidget = new MyWidget(pParent);	
	m_pDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), pParent);
}

//long IscsMock::GetWindows() 
//{
//	WId id = m_pMywidget->winId();
//
//	/*QString tip ;
//	tip.sprintf("m_pMywidget->winId = %d", id);	
//	QMessageBox::about(NULL, "Hi", tip);*/
//
//	return (long)(id);
//}

void IscsMock::SetParentWindow(WId parentWnd)
{
	m_wndParent = parentWnd;
}

WId IscsMock::GetWindows() 
{
	return (((QDateTimeEdit*)m_pDateTimeEdit)->winId());
}


void IscsMock::ShowWindow()
{
	((QDateTimeEdit*)m_pDateTimeEdit)->show();

	m_pMywidget->show();
}