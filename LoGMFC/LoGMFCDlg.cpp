
// LoGMFCDlg.cpp : 구현 파일
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

// CLoGMFCDlg 대화 상자

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


// CLoGMFCDlg 메시지 처리기
void CLoGMFCDlg::makeBitMap(uch *p_dest_image, uch ** p_src_image)
{
	uch* temp = new uch[ExtWidth * ExtWidth];
	for (int i = 0; i < ExtWidth; i++) {
		memcpy(temp + i * ExtWidth, p_src_image[i], ExtWidth);
	}
	p_dest_pos = p_dest_image;
	p_src_pos = temp;
	for (int i = 0; i < ExtWidth * ExtWidth; i++) {//8->32bit 전환
												   //RGB값을 동일하게 복사하여 흑백영상으로
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos;
		*p_dest_pos++ = *p_src_pos++;
		*p_dest_pos++ = 0xFF;
	}
	//32bit 이미지값을 CImage객체에 적용
	::SetBitmapBits(m_Image, ExtWidth * ExtWidth * 4, p_dest_image);
	delete[] temp;
}

BOOL CLoGMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_Image.Create(512, 512, 32);//32bit맵 생성
	m_LoG.makeImage(width, orginRaw);	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLoGMFCDlg::OnPaint()
{
	CPaintDC dc(this);// 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
