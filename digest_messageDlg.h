
// digest_messageDlg.h: 头文件
//

#pragma once


// CdigestmessageDlg 对话框
class CdigestmessageDlg : public CDialogEx
{
// 构造
public:
	CdigestmessageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGEST_MESSAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


public :
	void digest_message(char *path);
	void digest_message_SHA512(char *path);
	void digest_message_MD5(char *path);
	void handleErrors();

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString Path_F;
	CString DigestName;
	CString disgest_V1;
	CString disgest_v2;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
