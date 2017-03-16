
// LoGMFCDlg.h : ��� ����
//
#include "myImage.h"
#include "LoG.h"
#pragma once


// CLoGMFCDlg ��ȭ ����
class CLoGMFCDlg : public CDialogEx
{
private:
	LoG m_LoG;
	CImage m_Image;
	uch* p_src_pos = nullptr;
	uch* p_dest_pos = nullptr;
	uch state = 0;
	void makeBitMap(uch * p_dest_image, uch ** p_src_image);
// �����Դϴ�.
public:
	CLoGMFCDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;	
	ush ExtWidth = 512;
	// ������ �޽��� �� �Լ�
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
