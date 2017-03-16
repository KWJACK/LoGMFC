
// LoGMFCDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "LoGMFC.h"
#include "LoGMFCDlg.h"
#include "afxdialogex.h"
#include "myImage.h"
#include "LoG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define orginRaw "07_gLenna_512_512.raw"
#define edgeRaw "LoGLenna_512_512.raw"
#define ZCRaw "ZeroCrossingLenna_512_512.raw"
#define width 512

// CLoGMFCDlg ��ȭ ����

CLoGMFCDlg::CLoGMFCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoGMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoGMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLoGMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLoGMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLoGMFCDlg::OnBnClickedButton3)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLoGMFCDlg �޽��� ó����
void CLoGMFCDlg::makeBitMap(uch *p_dest_image, uch ** p_src_image)
{
	uch* temp = new uch[ExtWidth * ExtWidth];
	for (int i = 0; i < ExtWidth; i++) {
		memcpy(temp + i * ExtWidth, p_src_image[i], ExtWidth);
	}
	p_dest_pos = p_dest_image;
	p_src_pos = temp;
	for (int i = 0; i < ExtWidth * ExtWidth; i++) {//8->32bit ��ȯ
												   //RGB���� �����ϰ� �����Ͽ� ��鿵������
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos++;
		*p_dest_pos++ = 0xFF;
	}
	//32bit �̹������� CImage��ü�� ����
	::SetBitmapBits(m_Image, ExtWidth * ExtWidth * 4, p_dest_image);
	delete[] temp;
}

BOOL CLoGMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_Image.Create(512, 512, 32);//32bit�� ����
	m_LoG.makeImage(width, orginRaw);	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLoGMFCDlg::OnPaint()
{
	CPaintDC dc(this);// �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		if (state <= 0) {

		}
		else {
			uch *p_outImage = new uch[ExtWidth * ExtWidth * 4];
			switch (state)
			{
			case 1: {//LoG
				makeBitMap(p_outImage, m_LoG.getOutBuf());
				break;
			}
			case 2: {//initial
				makeBitMap(p_outImage, m_LoG.getInBuf());
				break;
			}
			default:
				break;
			}
			m_Image.Draw(dc, 10, 10);
			delete[] p_outImage;
			//CDialogEx::OnPaint();
		}
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLoGMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLoGMFCDlg::OnBnClickedButton1()
{
	m_LoG.exLog(0);
	m_LoG.writeFile(edgeRaw);
	state = 1;
	Invalidate(TRUE);
}


void CLoGMFCDlg::OnBnClickedButton2()
{
	state = 2;
	Invalidate(TRUE);
}


void CLoGMFCDlg::OnBnClickedButton3()
{
	m_LoG.exLog(1);
	m_LoG.writeFile(ZCRaw);
	state = 1;
	Invalidate(TRUE);
}


void CLoGMFCDlg::OnDestroy()
{//for invalid exit
	CDialogEx::OnDestroy();
	m_LoG.deleteLoG();
	m_LoG.deleteInOut2D();
}
