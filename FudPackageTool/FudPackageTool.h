
// FudPackageTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFudPackageToolApp: 
// �йش����ʵ�֣������ FudPackageTool.cpp
//

class CFudPackageToolApp : public CWinApp
{
public:
	CFudPackageToolApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFudPackageToolApp theApp;