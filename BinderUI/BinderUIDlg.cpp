
// BinderUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BinderUI.h"
#include "BinderUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBinderUIDlg �Ի���
#include "OpenSave.h"
void vmp(LPCTSTR lpszFileName)
{
	TCHAR szCmd[MAX_PATH] = { 0 };
	_stprintf_s(szCmd, _T("VMProtect_Con.exe %s"), lpszFileName);
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	RtlZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	GetStartupInfo(&si);
	RtlZeroMemory(&pi, sizeof(pi));
	si.wShowWindow = SW_SHOW;
	// Start the child process.   
	if (CreateProcess(NULL,   // No module name (use command line)  
		(LPSTR)szCmd,        // Command line  
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

CBinderUIDlg::CBinderUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BINDERUI_DIALOG, pParent),flags(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBinderUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBinderUIDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CBinderUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CBinderUIDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CBinderUIDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CBinderUIDlg ��Ϣ�������

BOOL CBinderUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	TCHAR szFileName[MAX_PATH] = { 0 };
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	*(_tcsrchr(szFileName, _T('\\')) + 1) = NULL;
	_tcsncpy(szDatFile, szFileName, MAX_PATH);
	_tcsncat(szDatFile, _T("fudpak.dat"), MAX_PATH);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBinderUIDlg::OnPaint()
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
HCURSOR CBinderUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CBinderUIDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwRet = GetOpenName(GetModuleHandle(NULL), szSrcExeFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("ԭʼEXE�ļ�"));
	if (dwRet)
	{
		//SetDlgItemText(IDC_ICONEXE, szIconExeFile);
		flags |= 2;
	}
}


void CBinderUIDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (flags!=3)
	{
		AfxMessageBox(_T("����ѡ�ú��ź�ԭʼ�ļ�"));
		return;
	}

	DWORD dwRet = GetSaveName(GetModuleHandle(NULL), szOutFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("����Ϊ?"));
	if(dwRet)
	{
		IconExchange(szSrcExeFile, szDatFile, szOutFile);
		auto rt = bind_file(szSrcExeFile, szBackDoorFile, szOutFile);
		if (rt)
		{
			vmp(szOutFile);
			AfxMessageBox(TEXT("����ɹ�"));
		}
		else
		{
			AfxMessageBox(TEXT("����ʧ��"));
		}
		CDialogEx::OnOK();
	}
}


void CBinderUIDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwRet = GetOpenName(GetModuleHandle(NULL), szBackDoorFile, TEXT("EXE (*.EXE)\0*.EXE\0"), TEXT("ѡ�����EXE�ļ�"));
	if (dwRet)
	{
		//SetDlgItemText(IDC_ICONEXE, szIconExeFile);
		flags |= 1;
	}
}
