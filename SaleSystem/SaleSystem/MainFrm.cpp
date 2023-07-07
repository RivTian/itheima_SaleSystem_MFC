
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SelectView.h"
#include "MainFrm.h"
#include "DisplayView.h"
#include "UserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE��Ӧ�����Զ�����Ϣ
	//����NM_X��Ϣ���Զ�����OnMyChange����
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//����ͼ�꣬IDI_ICON_WINΪͼ����ԴID����ΪWINAPI����
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//���ô��ڵ�λ�úʹ�С��CWnd::MoveWindow
	//0, 0, �������x��y
	//800, 500, ���ڿ�Ⱥ͸߶�
	MoveWindow(0, 0, 800, 500);

	//�������ƶ�����Ļ���룬CWnd::CenterWindow
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���

	// ��̬��ִ��ڣ� 1��2�У�CSplitterWndL::CreateStatic
	m_spliter.CreateStatic(this, 1, 2);

	// ������ͼ
	//0, 0 �� ���ڵ�0�е�0�е�λ��
	//RUNTIME_CLASS(CSelectView) ����Ҫͷ�ļ�#include "SelectView.h"�� CSelectView��SelectView.h������
	// CSize(250, 500)��ָ����ͼ��Ⱥ͸߶�
	//pContext �� ΪOnCreateClient()���һ���β�
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);

	//0, 1�� ���ڵ�0�е�1�е�λ��
	//CDispalyView����Ҫͷ�ļ�#include "DispalyView.h"
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);


	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	if (wParam == NM_A)
	{
		//MessageBox(TEXT("������Ϣ������أ�"));
		//���ؽ���
		Context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &Context);
		CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	return 0;
}
