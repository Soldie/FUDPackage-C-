
// BinderUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBinderUIApp: 
// �йش����ʵ�֣������ BinderUI.cpp
//

class CBinderUIApp : public CWinApp
{
public:
	CBinderUIApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBinderUIApp theApp;