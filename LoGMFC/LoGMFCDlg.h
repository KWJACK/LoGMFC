
// LoGMFCDlg.h : 헤더 파일
//
#include "myImage.h"
#include "LoG.h"
#pragma once


// CLoGMFCDlg 대화 상자
class CLoGMFCDlg : public CDialogEx
{
private:
	LoG m_LoG;
	CImage m_Image;
	uch* p_src_pos = nullptr;
	uch* p_dest_pos = nullptr;
	uch state = 0;
	void makeBitMap(uch * p_dest_image, uch ** p_src_image);
// 생성입니다.
public:
	CLoGMFCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;	
	ush ExtWidth = 512;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnDestroy();
};
