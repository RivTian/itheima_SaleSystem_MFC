
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SelectView.h"
#include "MainFrm.h"
#include "DisplayView.h"
#include "UserDlg.h"
#include "SellDlg.h"
#include "InfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE响应的是自定义消息
	//产生NM_X消息，自动调用OnMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO:  在此添加成员初始化代码
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
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	//设置图标，IDI_ICON_WIN为图标资源ID，此为WINAPI函数
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	//设置窗口的位置和大小：CWnd::MoveWindow
	//0, 0, 起点坐标x和y
	//800, 500, 窗口宽度和高度
	MoveWindow(0, 0, 800, 500);

	//将窗口移动到屏幕中央，CWnd::CenterWindow
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

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


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  在此添加专用代码和/或调用基类

	// 静态拆分窗口， 1行2列，CSplitterWndL::CreateStatic
	m_spliter.CreateStatic(this, 1, 2);

	// 创建视图
	//0, 0 ： 放在第0行第0列的位置
	//RUNTIME_CLASS(CSelectView) ：需要头文件#include "SelectView.h"， CSelectView在SelectView.h中声明
	// CSize(250, 500)：指定视图宽度和高度
	//pContext ： 为OnCreateClient()最后一个形参
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);

	//0, 1： 放在第0行第1列的位置
	//CDispalyView，需要头文件#include "DispalyView.h"
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);


	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext Context;
	if (wParam == NM_A)
	{
		//MessageBox(TEXT("个人信息界面挂载！"));
		//挂载界面
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
	if (wParam == NM_B)
	{
		Context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 500), &Context);
		CSellDlg *pNewView = (CSellDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	if (wParam == NM_C)
	{
		//CInfoDlg类需要包含头文件#include "InfoDlg.h"
		Context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		Context.m_pCurrentFrame = this;
		Context.m_pLastView = (CFormView *)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 0), &Context);
		CInfoDlg *pNewView = (CInfoDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
	}
	return 0;
}
