
// LoGMFC.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CLoGMFCApp:
// �� Ŭ������ ������ ���ؼ��� LoGMFC.cpp�� �����Ͻʽÿ�.
//

class CLoGMFCApp : public CWinApp
{
public:
	CLoGMFCApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CLoGMFCApp theApp;