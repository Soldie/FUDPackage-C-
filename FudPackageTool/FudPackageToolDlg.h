
// FudPackageToolDlg.h : ͷ�ļ�
//

#pragma once
#include "BmpButton.h"

// CFudPackageToolDlg �Ի���
class CFudPackageToolDlg : public CDialogEx
{
// ����
public:
	CFudPackageToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FUDPACKAGETOOL_DIALOG };
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
	afx_msg void OnBnClickedButton2();
public:
	TCHAR szExeFile[MAX_PATH];
	TCHAR szDllFile[MAX_PATH];
	TCHAR szOutFile[MAX_PATH];
	TCHAR szIconExeFile[MAX_PATH];
	TCHAR szInjectTargetName[MAX_PATH];
	TCHAR szSigFile[MAX_PATH];
	TCHAR szDatFile[MAX_PATH];
	afx_msg void OnBnClickedButton3();
	BOOL bExePack;
	afx_msg void OnBnClickedButton4();
	int flags;
	CRect m_rcCaption;	//�������ķ�Χ
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	LRESULT OnMsgButton(WPARAM, LPARAM);
	CBmpButton m_btnClose;	//�رհ�ť
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
