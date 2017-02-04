#include "stdafx.h"
#include "Base.h"
#include "ConfigData.h"
#include "PeFile.h"

CConfigData::CConfigData()
{
}


CConfigData::~CConfigData()
{
}

BOOL CConfigData::LoadConfig(LPCTSTR lpszFileName, PVOID outBuffer, UINT nOutSize)
{
	VMProtectBegin(__FUNCTION__);
	BOOL bRet = FALSE;
	HMODULE hModule = LoadLibraryEx(lpszFileName, NULL, LOAD_LIBRARY_AS_DATAFILE);
	if (hModule)
	{
		HRSRC hRes = FindResourceEx(hModule, CFG_RESTYPE, CFG_RESID, CFG_RESLANGID);
		if (hRes)
		{
			DWORD dwSize = SizeofResource(hModule, hRes);
			if (dwSize >= nOutSize)
			{
				HGLOBAL hResLoad = LoadResource(hModule, hRes);
				if (hResLoad)
				{
					LPVOID lpBuffer = LockResource(hResLoad);
					if (lpBuffer)
					{
						RtlCopyMemory(outBuffer, lpBuffer, nOutSize);
						bRet = TRUE;
					}
				}
			}
		}
		FreeLibrary(hModule);
	}
	VMProtectEnd();
	return bRet;
	
}


BOOL CConfigData::SaveConfigData(LPCTSTR lpszFileName, PVOID InBuffer, UINT nInSize)
{
	BOOL bRet = FALSE;
	CPeFile pefile;
	if (lpszFileName && PathFileExists(lpszFileName))
	{
		TCHAR szBakFile[MAX_PATH] = TEXT("");
		OutputDebugStringA("working");
		// ���������Ѵ��ڣ���ô��������Դ(ռλ��Դ���Ѵ���ǩ��)
		ULONG uSignDataOffset = pefile.GetConfigOffset(lpszFileName);
		if (uSignDataOffset == 0)
		{
			// ������Դ
			OutputDebugStringA("up1");
			if (!pefile._MyUpdateResource(lpszFileName, InBuffer, nInSize))
				return FALSE;

			// Overlay���ݴ���
			_sntprintf_s(szBakFile, MAX_PATH, _T("%s.bak"), lpszFileName);
			if (!CopyFile(lpszFileName, szBakFile, FALSE))
				return FALSE;
		}
		if (uSignDataOffset)
		{
			OutputDebugStringA("up2");
			bRet = pefile._MyUpdateResource2(lpszFileName, uSignDataOffset, InBuffer, nInSize);
		}
		else
		{
			OutputDebugStringA("up3");
			if (pefile._MyUpdateResource(lpszFileName, InBuffer, nInSize))
			{
				// ��Overlay���ݿ���ȥ
				bRet = pefile.RestoreOverlayData(lpszFileName, szBakFile);
			}
		}
		if (bRet)
			bRet = pefile.CalcCheckSum(lpszFileName);
		if (szBakFile[0])
			DeleteFile(szBakFile);
	}
	return bRet;
}
