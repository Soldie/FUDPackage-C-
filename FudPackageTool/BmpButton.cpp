#include "stdafx.h"
#include "BmpButton.h"


//��ť״̬����
#define STATE_COUNT	4


//��ť״̬
enum
{
	STATE_NONE = 0,	//��ǰ��겻�ٰ����ϣ���̬��
	STATE_MOVE,		//��ǰ����ڰ�����
	STATE_DOWN,		//��ǰ����ڰ����ϰ���
	STATE_DISABLE,	//��ǰ��������
};

//���״̬
enum
{
	MOUSE_FLAGS_NONE = 0,			//��ʼ״̬
	MOUSE_FLAGS_LBUTTONDOWN_IN,		//����������, ���ڰ�ť��״̬
	MOUSE_FLAGS_LBUTTONDOWN_OUT,	//����������, ���ڰ�ť��״̬
};


//IMPLEMENT_DYNAMIC(CBmpButton, CWnd)
CBmpButton::CBmpButton()
{
	this->m_uState = 0;
	this->m_uFlags = 0;

	this->m_hButtonDC = NULL;
	this->m_hButtonBmp = NULL;
}

CBmpButton::~CBmpButton()
{
	if(this->m_hButtonDC){::DeleteDC(this->m_hButtonDC); this->m_hButtonDC=NULL;}
	if(this->m_hButtonBmp){::DeleteObject(this->m_hButtonBmp);this->m_hButtonBmp=NULL;}
}

//����ͼƬ������ť����ť��С����ͼƬ��С���м���
BOOL CBmpButton::CreateButton(CWnd*  pParentWnd		//�����ھ��
				  , int x, int y					//��ť��x,y����
				  , LPCTSTR lpBmpPath				//ͼƬ��ַ���ð汾ֻ֧��BMP��ʽ��
				  , UINT uID)						//��ťID
{
	//���ݴ����ͼƬ��ַ������ͼƬ
	this->m_hButtonBmp = (HBITMAP)::LoadImage(NULL, lpBmpPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	return Create(NULL, NULL, WS_VISIBLE, CRect(x, y, x+1, y+1), pParentWnd, uID);
}


BEGIN_MESSAGE_MAP(CBmpButton, CWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


int CBmpButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	HDC hDC = ::GetDC(this->m_hWnd);
	this->m_hButtonDC = ::CreateCompatibleDC(hDC);
	::SelectObject(this->m_hButtonDC, this->m_hButtonBmp);
	::ReleaseDC(this->m_hWnd, hDC);

	//��ȡͼƬ��С
	BITMAP bm;
	::GetObject(this->m_hButtonBmp, sizeof(bm), &bm);
	this->m_szButton.cx = bm.bmWidth/STATE_COUNT;
	this->m_szButton.cy = bm.bmHeight;

	//���ƶ�X,Y���꣬���ı�Z�򣬲��ػ棬���ı䴰�ڴ�С
	SetWindowPos(NULL, 0, 0, this->m_szButton.cx, this->m_szButton.cy, SWP_NOMOVE|SWP_NOZORDER|SWP_NOREDRAW);

	return 0;
}


BOOL CBmpButton::OnEraseBkgnd(CDC *pDC)
{
	CRect rcWnd;
	this->GetClientRect(rcWnd);

	::BitBlt(pDC->m_hDC
		, 0, 0, this->m_szButton.cx, this->m_szButton.cy
		, this->m_hButtonDC
		, this->m_uState * this->m_szButton.cx
		, 0 ,SRCCOPY);

	return TRUE;
}

void CBmpButton::OnMouseMove(UINT ,CPoint pt)
{
	//���������жϵ�ǰ����Ƿ��ڰ�ť��
	//��Ϊ��ť�����á����񡱣����Կ������û�ڰ�ť��Ҳ�ᴥ������Ϣ
	//ֻ��WM_MOUSEMOVE �� WM_LBUTTONUP ���п�������겻�ڰ�ť�ϻᴥ�������µ���Ϣ����

	CRect rcClient;
	this->GetClientRect(rcClient);
	if( ::PtInRect(rcClient,pt) )
	{
		//�״��ƶ�����ť�ϣ����ػ�
		if(STATE_NONE == this->m_uState && MOUSE_FLAGS_NONE == this->m_uFlags)
		{
			this->m_uState = STATE_MOVE;
			this->m_uFlags = MOUSE_FLAGS_NONE;
			this->Invalidate();
			return;
		}

		//����ڰ�ť�ϣ����������ǰ���״̬
		//˵����ǰ����ǣ�����ڡ���������£������˰�ť��δ�������������ƶ����˰�ť��Χ�����ٴ��ƶ�����
		//����Windows��ť��ƹ淶����ʱ��ťӦ����Ϊ����״̬
		if(STATE_NONE == this->m_uState && MOUSE_FLAGS_LBUTTONDOWN_OUT == this->m_uFlags)
		{
			this->m_uState = STATE_DOWN;
			this->Invalidate();
			return;
		}
	}
	else if(STATE_DOWN == this->m_uState)
	{
		//��겻�ڰ�ť�ϣ�����״̬��������£�ȴ�ִ���������
		//˵����ǰ����ǣ�����ڰ�ť�ϰ��º�δ�����ƶ�����ť��Χ��
		//����Windows��ť��ƹ淶����ʱ��ťӦ��ʾΪ��̬��ʽ
		this->m_uFlags = MOUSE_FLAGS_LBUTTONDOWN_OUT;
		this->m_uState = STATE_NONE;
		this->Invalidate();
	}
	else if(STATE_NONE != this->m_uState)
	{
		this->m_uState = STATE_NONE;
		this->Invalidate();
	}

	//��������Ƴ���Ϣ���������ã������޷���ӦWM_MOUSELEAVE��Ϣ
	TRACKMOUSEEVENT te = {sizeof(TRACKMOUSEEVENT) ,TME_LEAVE ,m_hWnd, 1};
	::_TrackMouseEvent(&te);

}

void CBmpButton::OnMouseLeave()
{
	//����뿪�˰�ť��Χ
	//��Ҫ�����ò�����������ǰ���״̬�ƿ���ť��Χ�����ᴥ������
	this->m_uState = STATE_NONE;
	this->m_uFlags = MOUSE_FLAGS_NONE;

	this->Invalidate();
}

void CBmpButton::OnLButtonDown(UINT, CPoint pt)
{
	//������겶��
	this->SetCapture();

	this->m_uState = STATE_DOWN;
	this->m_uFlags = MOUSE_FLAGS_LBUTTONDOWN_IN;

	this->Invalidate();
}

void CBmpButton::OnLButtonUp(UINT ,CPoint pt)
{
	//ȡ������
	::ReleaseCapture();

	CRect rcClient;
	this->GetClientRect(rcClient);

	//����Windows��ť��ƹ淶����ť��Ϣ��Ͷ��Ӧ��������ڰ�ť��Χ�ڵ����ʱ��Ͷ��
	//�ʴ˴������ж��µ�ǰ���λ��
	if(::PtInRect(rcClient,pt) && STATE_DOWN == this->m_uState)
	{
		::PostMessage(::GetParent(this->m_hWnd), MSG_BMP_BUTTON, this->GetDlgCtrlID(), NULL);
	}

	//����״̬�û�Ĭ��ֵ
	this->m_uState = STATE_NONE;
	this->m_uFlags = MOUSE_FLAGS_NONE;

	this->Invalidate();
}