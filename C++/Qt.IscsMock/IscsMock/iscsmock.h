#ifndef ISCSMOCK_H
#define ISCSMOCK_H

#include "iscsmock_global.h"
#include "qwindowdefs_win.h"

class MyWidget;

class ISCSMOCK_EXPORT IscsMock
{
public:
	IscsMock();
	~IscsMock();

private:
	WId m_wndParent;

public:
	MyWidget* m_pMywidget;
	void* m_pDateTimeEdit;

	void Open(WId parentWnd);

	void SetParentWindow(WId parentWnd);
	WId GetWindows();
	void ShowWindow();
};

#endif // ISCSMOCK_H
