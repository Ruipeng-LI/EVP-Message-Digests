
// digest_messageDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "digest_message.h"
#include "digest_messageDlg.h"
#include "afxdialogex.h"
#include "afxdialogex.h"
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include<stdio.h>
#include <openssl/rand.h>
#include <cstringt.h>
#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CdigestmessageDlg 对话框



CdigestmessageDlg::CdigestmessageDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIGEST_MESSAGE_DIALOG, pParent)
	, Path_F(_T(""))
	, DigestName(_T(""))
	, disgest_V1(_T(""))
	, disgest_v2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdigestmessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Path_F);
	DDX_Text(pDX, IDC_EDIT2, DigestName);
	DDX_Text(pDX, IDC_EDIT3, disgest_V1);
	DDX_Text(pDX, IDC_EDIT4, disgest_v2);
}

BEGIN_MESSAGE_MAP(CdigestmessageDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CdigestmessageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CdigestmessageDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON6, &CdigestmessageDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON4, &CdigestmessageDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CdigestmessageDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CdigestmessageDlg 消息处理程序

BOOL CdigestmessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CdigestmessageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdigestmessageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CdigestmessageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CdigestmessageDlg::OnBnClickedButton2()  //添加文件路径
{
	// TODO: 在此添加控件通知处理程序代码

		// 显示文件打开对话框
	CFileDialog dlg(TRUE, NULL, _T("*.*"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"));
	if (dlg.DoModal() != IDOK) return;
	//获取文件的绝对路径 
	UpdateData();
	Path_F = dlg.GetPathName();
	UpdateData(FALSE);
}


void CdigestmessageDlg::OnBnClickedButton3()  //SHA256
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	;
	//CString转char*

	   //进行转换
	CString KL = Path_F;

	char *path = T2A(KL.GetBuffer(0));
	KL.ReleaseBuffer();
	digest_message(path);
	
	
	
	MessageBox(_T("成功！"), 0, 0);
	
}

void CdigestmessageDlg::digest_message(char *path)
	{
	EVP_MD_CTX *mdctx;
	unsigned char message[2048];
	int message_len = 0;
	unsigned char * digest=(unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()));
	unsigned int digest_len = 0;
	if((mdctx = EVP_MD_CTX_create()) == NULL)
		EVP_MD_CTX *mdctx;

	if ((mdctx = EVP_MD_CTX_create()) == NULL)
		handleErrors();

	if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))
		handleErrors();
	FILE *fpIn;
	fpIn = fopen((const char *)path, "rb");
	if (fpIn == NULL)
	{
		handleErrors();

	}
	for (;;)
	{

		message_len = fread(message, 1, 2048, fpIn);
		if (message_len <= 0)//读取原文结束
			break;
		if (1 != EVP_DigestUpdate(mdctx, message, message_len))
			handleErrors();

	}

	if (1 != EVP_DigestFinal_ex(mdctx, digest, &digest_len))
		handleErrors();
	
	EVP_MD_CTX_destroy(mdctx);
	int num = 0;
	char H[3] = { '0' };
	int j = 0;
	CString st;
	for (int i = 0;i<digest_len;i++)
	{
		num = digest[i];
		itoa(num, H, 16);
		if (H[1] == '\0')
		{
			H[1] = H[0];
			H[0] = '0';

		}
		st = st +H[0]+H[1];
	}

	UpdateData();
	DigestName = st;
	UpdateData(FALSE);
}

void CdigestmessageDlg::handleErrors() {

	MessageBox(_T("ERROR!"), 0, 0);
	exit(0);
}

void CdigestmessageDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	UpdateData(FALSE);

	if(disgest_V1== disgest_v2)
		MessageBox(_T("摘要信息一致"), 0, 0);
	else MessageBox(_T("摘要信息不一致"), 0, 0);
	
}


void CdigestmessageDlg::OnBnClickedButton4()  //SHA512
{
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	;
	//CString转char*

	   //进行转换
	CString KL = Path_F;

	char *path = T2A(KL.GetBuffer(0));
	KL.ReleaseBuffer();
	digest_message_SHA512(path);



	MessageBox(_T("成功！"), 0, 0);
}

void CdigestmessageDlg::digest_message_SHA512(char *path) {

	EVP_MD_CTX *mdctx;
	unsigned char message[2048];
	int message_len = 0;
	unsigned char * digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha512()));
	unsigned int digest_len = 0;
	if ((mdctx = EVP_MD_CTX_create()) == NULL)
		EVP_MD_CTX *mdctx;

	if ((mdctx = EVP_MD_CTX_create()) == NULL)
		handleErrors();

	if (1 != EVP_DigestInit_ex(mdctx, EVP_sha512(), NULL))
		handleErrors();
	FILE *fpIn;
	fpIn = fopen((const char *)path, "rb");
	if (fpIn == NULL)
	{
		handleErrors();

	}
	for (;;)
	{

		message_len = fread(message, 1, 2048, fpIn);
		if (message_len <= 0)//读取原文结束
			break;
		if (1 != EVP_DigestUpdate(mdctx, message, message_len))
			handleErrors();

	}

	if (1 != EVP_DigestFinal_ex(mdctx, digest, &digest_len))
		handleErrors();

	EVP_MD_CTX_destroy(mdctx);
	int num = 0;
	char H[3] = { '0' };
	int j = 0;
	CString st;
	for (int i = 0; i < digest_len; i++)
	{
		num = digest[i];
		itoa(num, H, 16);
		if (H[1] == '\0')
		{
			H[1] = H[0];
			H[0] = '0';

		}
		st = st + H[0] + H[1];
	}

	UpdateData();
	DigestName = st;
	UpdateData(FALSE);

}

void CdigestmessageDlg::OnBnClickedButton5()  //MD5
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	USES_CONVERSION;
	;
	//CString转char*

	   //进行转换
	CString KL = Path_F;

	char *path = T2A(KL.GetBuffer(0));
	KL.ReleaseBuffer();
	digest_message_MD5(path);



	MessageBox(_T("成功！"), 0, 0);
}

void CdigestmessageDlg::digest_message_MD5(char *path) {

	EVP_MD_CTX *mdctx;
	unsigned char message[2048];
	int message_len = 0;
	unsigned char * digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_md5()));
	unsigned int digest_len = 0;
	if ((mdctx = EVP_MD_CTX_create()) == NULL)
		EVP_MD_CTX *mdctx;

	if ((mdctx = EVP_MD_CTX_create()) == NULL)
		handleErrors();

	if (1 != EVP_DigestInit_ex(mdctx, EVP_md5(), NULL))
		handleErrors();
	FILE *fpIn;
	fpIn = fopen((const char *)path, "rb");
	if (fpIn == NULL)
	{
		handleErrors();

	}
	for (;;)
	{

		message_len = fread(message, 1, 2048, fpIn);
		if (message_len <= 0)//读取原文结束
			break;
		if (1 != EVP_DigestUpdate(mdctx, message, message_len))
			handleErrors();

	}

	if (1 != EVP_DigestFinal_ex(mdctx, digest, &digest_len))
		handleErrors();

	EVP_MD_CTX_destroy(mdctx);
	int num = 0;
	char H[3] = { '0' };
	int j = 0;
	CString st;
	for (int i = 0; i < digest_len; i++)
	{
		num = digest[i];
		itoa(num, H, 16);
		if (H[1] == '\0')
		{
			H[1] = H[0];
			H[0] = '0';

		}
		st = st + H[0] + H[1];
	}

	UpdateData();
	DigestName = st;
	UpdateData(FALSE);

}