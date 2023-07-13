// SellDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SaleSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"

// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(CSellDlg::IDD)
	, m_price(0)
	, m_num(0)
	, m_sellinfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT4, m_num);
	DDX_Text(pDX, IDC_EDIT2, m_sellinfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSellDlg ���

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg ��Ϣ�������


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO:  �ڴ����ר�ô����/����û���
	CInfoFile file;
	file.ReadDocline();  // ��ȡ��Ʒ
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	// for (auto it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear(); // ���list ����

	m_combo.SetCurSel(0);
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString text;

	int idx = m_combo.GetCurSel();
	m_combo.GetLBText(idx, text);

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	// for (auto it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (text == it->name.c_str())
		{
			m_price = it->price;
			m_num = it->num;
			UpdateData(FALSE);
		}
	}

	file.ls.clear(); // ���list ����
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//��ȡ�ؼ��ϵ����ݣ����µ���Ӧ�����ı�����
	UpdateData(TRUE);

	if (m_num == 0)
	{
		MessageBox(TEXT("��������Ϊ0"));
		return;
	}

	CString type;
	//��ȡ��ǰѡ����
	int index = m_combo.GetCurSel();
	//��ȡ��Ͽ�ǰ����
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(_T("��Ʒ��%s \r\n���ۣ�%d \r\n������%d \r\n�ܼۣ�%d"), type, m_price, m_num, m_price*m_num);

	m_sellinfo = str; //������Ϣ
	UpdateData(FALSE);
	MessageBox(str);


	//��Ҫ����#include "InfoFile.h"
	CInfoFile file;
	file.ReadDocline(); //��ȡ��Ʒ��Ϣ
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (type == it->name.c_str())
		{
			it->num = it->num - m_num;
		}
	}
	file.WirteDocline(); //�����ļ�����

	file.ls.clear(); //���list������

	m_sellinfo.Empty();
	m_num = 0;
	UpdateData(FALSE); //���µ���Ӧ�Ŀؼ�
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_combo.SetCurSel(0); //ѡ���0��Ŀ
	m_sellinfo = "";
	m_num = 0;
	OnCbnSelchangeCombo1();
}