
// LoGMFC.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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


// CLoGMFCApp 생성

CLoGMFCApp::CLoGMFCApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CLoGMFCApp 개체입니다.

CLoGMFCApp theApp;


// CLoGMFCApp 초기화

BOOL CLoGMFCApp::InitInstance()
{
	CWinApp::InitInstance();
	CLoGMFCDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	//eliminate all serviced code for avoiding not to register in system
	return FALSE;
}

