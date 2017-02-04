/*********************************************************************************************
���ǻ���CWnd����д�İ�ť�࣬�ð汾��֧��BMP�ļ���ͼƬ��Դ
����ʵ�ֵ�ͼƬ��ť����ѭ΢��İ�ť��׼
ͼƬ��Դ��ʽ����������У���С��ȵ�4����ť״̬���ɲο�ʾ�������е���Դ�ļ���
��ť״̬����ͨ-�������-��갴ť-����
����Ϊ��ʾ��ѧ�ã���ʵ��������������ݣ��������ݿ���������
**********************************************************************************************/


/*********************************************************************************************

C/C++/MFC/VC��������ѧϰȺ��197778914����ӭ���ļ��룡

**********************************************************************************************/


#pragma once


#define MSG_BMP_BUTTON	(WM_USER + 1001)	//��ť��Ϣ


//////////////////////////////////////////////////////////////////////////////////////////////////
//Class's
class CBmpButton : public CWnd
{
public:
	CBmpButton();
	virtual ~CBmpButton();

public:
	//����ͼƬ������ť����ť��С����ͼƬ��С���м���
	BOOL CreateButton(CWnd*  pParentWnd	//�����ھ��
		, int x, int y					//��ť��x,y����
		, LPCTSTR lpBmpPath				//ͼƬ��ַ���ð汾ֻ֧��BMP��ʽ��
		, UINT uID);					//��ťID

protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC *pDC);
	afx_msg void OnLButtonDown(UINT, CPoint);
	afx_msg void OnLButtonUp(UINT ,CPoint);
	afx_msg void OnMouseMove(UINT, CPoint);
	afx_msg void OnMouseLeave();

	DECLARE_MESSAGE_MAP()

private:
	UINT    m_uState;		//��ǰ��ť״̬
	UINT    m_uFlags;		//��ǰ���״̬

	SIZE	m_szButton;		//��ť��С

	HDC     m_hButtonDC;	//��ťͼƬDC
	HBITMAP m_hButtonBmp;	//��ťͼƬBMP
};