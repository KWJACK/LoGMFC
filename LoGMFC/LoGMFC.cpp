
// LoGMFC.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "LoGMFC.h"
#include "LoGMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoGMFCApp

BEGIN_MESSAGE_MAP(CLoGMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLoGMFCApp ����

CLoGMFCApp::CLoGMFCApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CLoGMFCApp ��ü�Դϴ�.

CLoGMFCApp theApp;


// CLoGMFCApp �ʱ�ȭ

BOOL CLoGMFCApp::InitInstance()
{
	CWinApp::InitInstance();
	CLoGMFCDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	//eliminate all serviced code for avoiding not to register in system
	return FALSE;
}

