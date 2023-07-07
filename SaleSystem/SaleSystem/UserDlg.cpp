// UserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "UserDlg.h"
#include "InfoFile.h"

// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(CUserDlg::IDD)
	, m_user(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
	, m_name(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
	DDX_Text(pDX, IDC_EDIT2, m_name);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg ���

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg ��Ϣ�������


// ��ʼ������
void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CInfoFile file;		// ��Ҫͷ�ļ� "InfoFile.h"
	CString name, pwd;
	file.ReadLogin(name, pwd); // ��ȡ�ļ����û���������

	// init persone info
	m_user = _T("����Ա");
	m_name = name;

	UpdateData(FALSE); // �����ݸ��µ��ؼ���
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE); // ���¿ؼ����ݵ���Ӧ�ı�����

	// �ǿ�
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(_T("�������벻��Ϊ��"));
		return;
	}

	if (m_newPwd != m_surePwd)
	{
		MessageBox(_T("�����������벻ƥ��"));
		return;
	}

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (m_surePwd == pwd)
	{
		MessageBox(_T("��������;��������"));
		return;
	}

	//���û����������CString����תΪchar *
	// ��Ϊ WritePwd �� char * ����
	char *tmpName, *tmpPwd;
	CStringA tmp1;
	tmp1 = name;
	tmpName = tmp1.GetBuffer();

	CStringA tmp2;
	tmp2 = m_surePwd;
	tmpPwd = tmp2.GetBuffer();

	file.WritePwd(tmpName, tmpPwd);

	MessageBox(_T("�����޸ĳɹ�"));

	//������������
	m_surePwd.Empty();
	m_newPwd.Empty();
	UpdateData(FALSE); //�����ݸ��µ��ؼ���
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//������������
	m_surePwd.Empty();
	m_newPwd.Empty();
	UpdateData(FALSE); //�����ݸ��µ��ؼ���
}
