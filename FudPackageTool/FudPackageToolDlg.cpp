
// FudPackageToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FudPackageTool.h"
#include "FudPackageToolDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BORDER_WIDTH 7		//�߿�Ŀ��
#define ID_BTN_CLOSE 9999	//�رհ�ťID

// CFudPackageToolDlg �Ի���
DWORD GetSaveName(HINSTANCE hInstance, TCHAR* outbuf, const TCHAR* filter, const TCHAR* title);
DWORD GetOpenName(HINSTANCE hInstance, TCHAR* outbuf, const TCHAR* filter, const TCHAR* title);
using T_vmprotect = void (WINAPI *)(LPCSTR lpszFileName);
void wmp(LPCTSTR lpszFileName)
{
	auto p = LoadLibraryA("WProtect.dll");
	auto ptr_func = (T_vmprotect)GetProcAddress(p, "vmprotect");
	ptr_func(lpszFileName);
}
void vmp(LPCTSTR lpszFileName)
{
	CString m_cmd;
	m_cmd.Format(_T("VMProtect_Con.exe %s"), lpszFileName);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	RtlZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	GetStartupInfo(&si);
	RtlZeroMemory(&pi, sizeof(pi));
	si.wShowWindow = SW_SHOW;
	// Start the child process.   
	if (CreateProcess(NULL,   // No module name (use command line)  
		(LPSTR)m_cmd.GetBuffer(0),        // Command line  
		NULL,           // Process handle not inheritable  
		NULL,           // Thread handle not inheritable  
		FALSE,          // Set handle inheritance to FALSE  
		0,              // No creation flags  
		NULL,           // Use parent's environment block  
		NULL,           // Use parent's starting directory   
		&si,            // Pointer to STARTUPINFO structure  
		&pi)
		)
	{

		WaitForSingleObject(pi.hProcess, INFINITE);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
}

CFudPackageToolDlg::CFudPackageToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FUDPACKAGETOOL_DIALOG, pParent)
	, bExePack(FALSE)
	, flags(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFudPackageToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFudPackageToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFudPackageToolDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CFudPackageToolDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFudPackageToolDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CFudPackageToolDlg::OnBnClickedButton4)
	ON_WM_ERASEBKGND()
	ON_MESSAGE(MSG_BMP_BUTTON, OnMsgButton)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CFudPackageToolDlg ��Ϣ�������

BOOL CFudPackageToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	((CWnd *)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	//((CWnd *)GetDlgItem(IDC_BUTTON4))->EnableWindow(FALSE);
	TCHAR szFileName[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	*(_tcsrchr(szFileName, _T('\\')) + 1) = NULL;
	_tcsncpy(szSigFile, szFileName, MAX_PATH);
	_tcsncpy(szDatFile, szFileName, MAX_PATH);
	_tcsncat(szDatFile, _T("fudpak.dat"), MAX_PATH);
	_tcsncat(szSigFile, _T("sig.pak"), MAX_PATH);

	CRect rcWnd;
	this->GetClientRect(&rcWnd);

	m_rcCaption.left = 0;
	m_rcCaption.top = 0;
	m_rcCaption.right = rcWnd.Width();
	m_rcCaption.bottom = 29;

	m_btnClose.CreateButton(this, rcWnd.Width() - BORDER_WIDTH - 36, 5, _T("cloase.bmp"), ID_BTN_CLOSE);
	//AfxMessageBox(szSigFile);
	//AfxMessageBox(szDatFile);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFudPackageToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFudPackageToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFudPackageToolDlg::OnBnClickedButton1()
{
	DWORD dwRet = GetOpenName(GetModuleHandle(NULL), szExeFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("ѡ��EXE�ļ�"));
	if (dwRet)
	{
		SetDlgItemText(IDC_EXE, szExeFile);
		((CWnd *)GetDlgItem(IDC_BUTTON3))->EnableWindow(FALSE);
		bExePack = TRUE;
		((CWnd *)GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
		flags |= 1;
	}
}


void CFudPackageToolDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwRet = GetOpenName(GetModuleHandle(NULL), szIconExeFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("ѡ���ṩͼ���EXE�ļ�"));
	if (dwRet)
	{
		SetDlgItemText(IDC_ICONEXE, szIconExeFile);
		flags |= 2;
	}
}


void CFudPackageToolDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwRet = GetOpenName(GetModuleHandle(NULL), szDllFile, TEXT("Dll (*.DLL)\0*.DLL\0"), TEXT("ѡ��DLL�ļ�"));
	if (dwRet)
	{
		SetDlgItemText(IDC_DLL, szDllFile);
		((CWnd *)GetDlgItem(IDC_BUTTON1))->EnableWindow(FALSE);
		bExePack = FALSE;
		((CWnd *)GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
		flags |= 1;
	}
}


void CFudPackageToolDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (flags != 3)
	{
		if (flags == 1)
			AfxMessageBox(_T("����Ҫѡ��ͼ���ṩ��!!"));
		if (flags == 2)
			AfxMessageBox(_T("����Ҫ��DLL����EXE֮��ѡһ������"));
		if (flags == 0)
			AfxMessageBox(_T("����ֱ������EXE"));
		return;
	}
	DWORD dwRet = GetSaveName(GetModuleHandle(NULL), szOutFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("����Ϊ?"));
	if (dwRet)
	{
		IconExchange(szIconExeFile, szDatFile, szOutFile);
		if (bExePack)
		{
			//CopyFile(_T("fudpak.dat"), szOutFile, FALSE);
			auto b_ret = pack_file(szSigFile, szExeFile, szOutFile);
			if (b_ret)
			{
				vmp(szOutFile);
				AfxMessageBox(_T("���ok"));
				return CDialogEx::OnOK();
			}
		}
		else
		{
			GetDlgItemText(IDC_EDIT1, szInjectTargetName, MAX_PATH);
			if (_tcslen(szInjectTargetName) <= 3)
			{
				AfxMessageBox(_T("������һ���Ϸ���ע��Ŀ��"));
				return;
			}
			auto b_ret = pack_file_dll(szDllFile, szInjectTargetName, szOutFile);
			if (b_ret)
			{
				vmp(szOutFile);

				AfxMessageBox(_T("���ok"));
				return CDialogEx::OnOK();
			}
		}
	}
	AfxMessageBox(_T("���ʧ��"));
	return CDialogEx::OnOK();
}


BOOL CFudPackageToolDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rcWnd;
	this->GetClientRect(&rcWnd);

	/*
	������ǽ������������ͱ߿򶼵�Ϊһ����ɫ�������Ļ�
	��ʵ����������൱����������
	һ��ȫ��ɫ�Ľ��棬�����������һ���ɫ������
	*/

	//1 - ���������涼����Ϊ��ɫ
	//pDC->FillRect(rcWnd, &CBrush(0x8FC5ED));	//��ɫ
	pDC->FillRect(rcWnd, &CBrush(RGB(96, 174, 210)));	//��ɫ

														//2 - ���������������߿򲿷ֵ����µķ�Χ��ȫ���ð�ɫ���
	CRect rc;
	rc.left = BORDER_WIDTH;
	rc.top = m_rcCaption.Height();
	rc.right = rcWnd.Width() - BORDER_WIDTH;
	rc.bottom = rcWnd.Height() - BORDER_WIDTH;
	pDC->FillRect(rc, &CBrush(0xF0F0F0));	//��ɫ

											//����ͼ��
	::DrawIconEx(pDC->m_hDC, BORDER_WIDTH, BORDER_WIDTH
		, m_hIcon, 16, 16, NULL, NULL, DI_NORMAL);

	//���Ʊ�������
	LOGFONT lf;
	::ZeroMemory(&lf, sizeof(lf));
	_stprintf(lf.lfFaceName, _T("΢���ź�"));

	CFont font;
	font.CreatePointFontIndirect(&lf);
	CFont* pFontOld = (CFont*)pDC->SelectObject(&font);	//���ｫѡ��ǰ������ָ�������
	pDC->SetBkMode(TRANSPARENT);	//һ��Ҫ�ǵ����������������а�ɫ�ĵ�ɫ
	CString sCaption;
	this->GetWindowText(sCaption);
	pDC->DrawText(sCaption, m_rcCaption, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//���������ڴ����м��ٻ���һ�λ�������Ч����
	/*pDC->DrawText(_T("C/C++/VC/MFC��������Ⱥ��197778914����ӭ��ļ��롣")
		, -1
		, rcWnd
		, DT_CENTER | DT_VCENTER | DT_SINGLELINE);*/

	pDC->SelectObject(pFontOld);	//��֮ǰ�������ѡ��ȥ
	font.DeleteObject();

	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

LRESULT CFudPackageToolDlg::OnMsgButton(WPARAM wParam, LPARAM)
{
	switch (wParam)
	{
	case ID_BTN_CLOSE:
		this->PostMessage(WM_CLOSE);
		break;

	default:
		break;
	}

	return 0;
}

LRESULT CFudPackageToolDlg::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToClient(&point);

	if (m_rcCaption.PtInRect(point))
		return HTCAPTION;

	return CDialogEx::OnNcHitTest(point);
}
