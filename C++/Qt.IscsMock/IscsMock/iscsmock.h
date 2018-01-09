#ifndef ISCSMOCK_H
#define ISCSMOCK_H

#include "iscsmock_global.h"

class MyWidget;

class ISCSMOCK_EXPORT IscsMock
{
public:
	IscsMock();
	~IscsMock();

private:

public:
	MyWidget* m_pMywidget;

	long GetWindows();
	void ShowWindow(long parent);
};

#endif // ISCSMOCK_H
