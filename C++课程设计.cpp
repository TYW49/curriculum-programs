// CosFunc.cpp: implementation of the CCosFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "CosFunc.h"
#include <AFXTEMPL.H>
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCosFunc::CCosFunc(double A,double b,double c,double P,double m,double n,int mutiple,
				   int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{

	m_dCos_A=A;
	m_dCos_b=b;
	m_dCos_c=c;
	m_dCos_P=P;
	m_dCos_m=m;
	m_dCos_n=n;
}

CCosFunc::~CCosFunc()
{

}

void CCosFunc::Draw(CDC *pDC,HWND hWnd)
{
	CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
    CString str1,str2,str3,str4,str;
    str1.Format("%.2f",m_dCos_A);
    str2.Format("%.2f",m_dCos_b);
	str3.Format("%.2f",m_dCos_c);
	str4.Format("%.2f",m_dCos_P);
	str="y="+str1+"Cos("+str2+"x"+str3+")"+"+"+str3;
	pDC->TextOut((int)(m_dCos_n*100)*m_nMutiple,(int)((m_dCos_A*cos(m_dCos_b*m_dCos_n+m_dCos_c)+m_dCos_P)*100*m_nMutiple),str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;  //模板数组
	double  k;
	int sum;  
	int i;
	CPoint p;
	for(k=m_dCos_m;k<m_dCos_n;k+=0.01)   //对图像进行采样点 
	{
          sum=(int)((m_dCos_A*cos(m_dCos_b*k+m_dCos_c)+m_dCos_P)*100*m_nMutiple);
		  p.x=k*100*m_nMutiple;
		  p.y=sum;
		  if(p.x<=1000&&p.x>=-1000)
			  m_Array.Add(p);
	}
	int  n=m_Array.GetSize();
	for(i=0;i<n-1;i++)   //绘制图像
	{
		pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
IMPLEMENT_SERIAL(CCosFunc,CLineType,0)
void CCosFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_dCos_A<<m_dCos_b<<m_dCos_c<<m_dCos_P<<m_dCos_m<<m_dCos_n;
	}
	else
	{
		ar>>m_dCos_A>>m_dCos_b>>m_dCos_c>>m_dCos_P>>m_dCos_m>>m_dCos_n;
	}
}

// DoubleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "DoubleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDoubleDlg dialog


CDoubleDlg::CDoubleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoubleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDoubleDlg)
	m_da = 0.0;
	m_db = 0.0;
	m_dc = 0.0;
	m_dm = 0.0;
	m_dn = 0.0;
	//}}AFX_DATA_INIT
}


void CDoubleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDoubleDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_da);
	DDX_Text(pDX, IDC_EDIT_B, m_db);
	DDX_Text(pDX, IDC_EDIT_C, m_dc);
	DDX_Text(pDX, IDC_EDIT_M, m_dm);
	DDX_Text(pDX, IDC_EDIT_N, m_dn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDoubleDlg, CDialog)
	//{{AFX_MSG_MAP(CDoubleDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDoubleDlg message handlers

// DoubleFunc.cpp: implementation of the DoubleFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "DoubleFunc.h"
#include <AFXTEMPL.H>
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#define Max 10000000000
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DoubleFunc::DoubleFunc(double a,double b,double c,double m,double n,int mutiple,
		int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{
	m_da=a;
	m_db=b;
	m_dc=c;
	m_dm=m;
	m_dn=n;
}

DoubleFunc::~DoubleFunc()
{

}

void  DoubleFunc::Draw(CDC *pDC,HWND hWnd)
{
    CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作 
	CString str1,str2,str3,str;
    str1.Format("%.2f",m_da);
    str2.Format("%.2f",m_db);
	str3.Format("%.2f",m_dc);
	str="y="+str1+"x^2"+"+"+str2+"x"+"+"+str3;
	pDC->TextOut((int)(m_dn*100*m_nMutiple),300,str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;//模板数组
	CPoint p;
	double k;
	int i,sum;
	for(k=m_dm;k<m_dn;k+=0.1)
	{
		sum=(int)((m_da*k*k+m_db*k+m_dc)*100*m_nMutiple);
		p.x=(int)(k*100*m_nMutiple);
		p.y=sum;
		if(p.x<=1000&&p.x>=-1000)
			  m_Array.Add(p);
		
	}
	int  n=m_Array.GetSize();
	for(i=0;i<n-1;i++)   //绘制图像
	{
		pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
    pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
}

IMPLEMENT_SERIAL(DoubleFunc,CLineType,0)
void DoubleFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_da<<m_db<<m_dc<<m_dm<<m_dn;
	}
	else
	{
		ar>>m_da>>m_db>>m_dc>>m_dm>>m_dn;
	}

}

// ExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "ExpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExpDlg dialog


CExpDlg::CExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExpDlg)
	m_da = 0.0;
	m_dm = 0.0;
	m_dn = 0.0;
	//}}AFX_DATA_INIT
}


void CExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExpDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_da);
	DDX_Text(pDX, IDC_EDIT_M, m_dm);
	DDX_Text(pDX, IDC_EDIT_N, m_dn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExpDlg, CDialog)
	//{{AFX_MSG_MAP(CExpDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExpDlg message handlers

// ExpFunc.cpp: implementation of the CExpFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "ExpFunc.h"
#include <AFXTEMPL.H>
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExpFunc::CExpFunc(double a,double m,double n,int mutiple,
					   int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{
	m_da=a;
	m_dm=m;
	m_dn=n;
}

CExpFunc::~CExpFunc()
{

}
void  CExpFunc::Draw(CDC *pDC,HWND hWnd)
{
    CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
	CString str1,str;
    str1.Format("%.2f",m_da);
	str="y="+str1+"^x";
	pDC->TextOut((int)(m_dn*100*m_nMutiple),(int)(pow(m_da,m_dn)*100*m_nMutiple),str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;  //模板数组
	CPoint p;
	double k;
	int i,sum;
	for(k=m_dm;k<m_dn;k+=0.1)
	{
		sum=(int)(pow(m_da,k)*100*m_nMutiple);
		p.x=(int)(k*100*m_nMutiple);
		p.y=sum;
		if(p.x<=1000&&p.x>=-1000)
			  m_Array.Add(p);
	}
	int  n=m_Array.GetSize();
	for(i=0;i<n-1;i++)   //绘制图像
	{
		pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
    pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	
}
IMPLEMENT_SERIAL(CExpFunc,CLineType,0)
void CExpFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_da<<m_dm<<m_dn;
	}
	else
	{
		ar>>m_da>>m_dm>>m_dn;
	}

}

// Huitu.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Huitu.h"

#include "MainFrm.h"
#include "HuituDoc.h"
#include "HuituView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuituApp

BEGIN_MESSAGE_MAP(CHuituApp, CWinApp)
	//{{AFX_MSG_MAP(CHuituApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuituApp construction

CHuituApp::CHuituApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHuituApp object

CHuituApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHuituApp initialization

BOOL CHuituApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CHuituDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CHuituView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);   //修改主窗口图标
	m_pMainWnd->SetIcon(hIcon,TRUE);
	m_pMainWnd->SetIcon(hIcon,FALSE);
    m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CHuituApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CHuituApp message handlers

// HuituDoc.cpp : implementation of the CHuituDoc class
//

#include "stdafx.h"
#include "Huitu.h"

#include "HuituDoc.h"
#include "LineType.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuituDoc

IMPLEMENT_DYNCREATE(CHuituDoc, CDocument)

BEGIN_MESSAGE_MAP(CHuituDoc, CDocument)
	//{{AFX_MSG_MAP(CHuituDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuituDoc construction/destruction

CHuituDoc::CHuituDoc()
{
	// TODO: add one-time construction code here

}

CHuituDoc::~CHuituDoc()
{
}

BOOL CHuituDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}
void CHuituDoc::RemoveList()
{
	POSITION pos=m_FigureList.GetHeadPosition();
	while(pos!=0)
	{
		CLineType *p=(CLineType *)m_FigureList.GetNext(pos);
		delete p;
	}
    m_FigureList.RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CHuituDoc serialization

void CHuituDoc::Serialize(CArchive& ar)
{
	m_FigureList.Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHuituDoc diagnostics

#ifdef _DEBUG
void CHuituDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHuituDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHuituDoc commands

void CHuituDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	RemoveList();
	CDocument::DeleteContents();
}

// HuituView.cpp : implementation of the CHuituView class
//

#include "stdafx.h"
#include "Huitu.h"

#include "HuituDoc.h"
#include "HuituView.h"

#include "SinFunc.h"
#include "SinDlg.h"
#include "CosFunc.h"
#include "TanDlg.h"
#include "TanFunc.h"
#include "LineTypeDlg.h"
#include "LinearFunc.h"
#include "LinearDlg.h"
#include "PowerFunc.h"
#include "PowerDlg.h"
#include "ExpFunc.h"
#include "ExpDlg.h"
#include "DoubleDlg.h"
#include "DoubleFunc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHuituView

IMPLEMENT_DYNCREATE(CHuituView, CView)

BEGIN_MESSAGE_MAP(CHuituView, CView)
	//{{AFX_MSG_MAP(CHuituView)
	ON_COMMAND(ID_CREATE_SIN, OnCreateSin)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_CREATE_COS, OnCreateCos)
	ON_COMMAND(ID_CREATE_TAN, OnCreateTan)
	ON_COMMAND(ID_LINE_TYPE, OnLineType)
	ON_COMMAND(ID_CREATE_POWER, OnCreatePower)
	ON_COMMAND(ID_CREATE_EXP, OnCreateExp)
	ON_COMMAND(ID_BUTTON_RED, OnButtonRed)
	ON_COMMAND(ID_BUTTON_GREEN, OnButtonGreen)
	ON_COMMAND(ID_BUTTON_BLUE, OnButtonBlue)
	ON_COMMAND(ID_ENLARGE, OnEnlarge)
	ON_COMMAND(ID_RECOVER, OnRecover)
	ON_COMMAND(ID_REDUCE, OnReduce)
	ON_COMMAND(ID_CREATE_DOUBLE, OnCreateDouble)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHuituView construction/destruction

CHuituView::CHuituView()
{
	// TODO: add construction code here
	m_pToolTip=NULL;
	m_nMutiple=1;  
	m_nLineType=PS_SOLID;
	m_nLineWidth=1;
	m_LineColor=RGB(0,0,0);

}

CHuituView::~CHuituView()
{
}

BOOL CHuituView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHuituView drawing

void CHuituView::OnDraw(CDC* pDC)
{
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    POSITION pos=pDoc->m_FigureList.GetHeadPosition();

    //绘制坐标系
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_LOMETRIC);
	pDC->SetWindowOrg(0,0); //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right / 2, rect.bottom / 2));//平移设备坐标系原点的操作
    //right、bottom分别表示矩形右下角顶点的横坐标和纵坐标
	CPen pen1(PS_SOLID, 1, RGB(255, 255, 0));
	CPen *pOldPen = pDC->SelectObject(&pen1);
	CString  str;
    int   x,y;
	int i,j;
	//坐标轴
	for(i =-1000; i <= 1000; i += 100*m_nMutiple)
	{
		x=i/(100*m_nMutiple);
		str.Format("%d",x);
		if(x!=0)
		{
			pDC->TextOut(i+10,-10,str);
		}
	}
	
	for (j=-600; j <=600; j+=100*m_nMutiple)
	{
		y=j/(100*m_nMutiple);
		str.Format("%d",y);
		if(y!=0)
		{
			pDC->TextOut(-50,j,str);
		}
	}
	
	pDC->TextOut(10, 650, "y");
	pDC->TextOut(-10,620,"^");
	pDC->TextOut(980,28,">");
	pDC->TextOut(1080, 30, "x");
	pDC->TextOut(0, 0, "0");
	CPen pen(PS_SOLID, 8, RGB(0, 0, 0));
	pOldPen =pDC->SelectObject(&pen);
    pDC->MoveTo(-1000, 0); //横坐标
	pDC->LineTo(1000, 0);
	pDC->MoveTo(0, -600);//纵坐标
	pDC->LineTo(0, 600);
    //图元链表
	while(pos!=NULL)
	{
		CLineType *p=(CLineType*)pDoc->m_FigureList.GetNext(pos);
	    p->m_nMutiple=m_nMutiple;
		p->Draw(pDC,*this);
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CHuituView printing

BOOL CHuituView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHuituView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHuituView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHuituView diagnostics

#ifdef _DEBUG
void CHuituView::AssertValid() const
{
	CView::AssertValid();
}

void CHuituView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuituDoc* CHuituView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuituDoc)));
	return (CHuituDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHuituView message handlers

void CHuituView::OnCreateSin() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC;
	pDC=GetDC();
	CSinFunc *m=new CSinFunc;
	CSinDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
        m->m_dSin_A=dlg.m_dSin_A;
		m->m_dSin_b=dlg.m_dSin_b;
		m->m_dSin_c=dlg.m_dSin_c;
		m->m_dSin_m=dlg.m_dSin_m;
		m->m_dSin_n=dlg.m_dSin_n;
		m->m_dSin_P=dlg.m_dSin_P;
		m->m_LineColor=	m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}
	
}

//创建工具提示控件
void CHuituView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC;
	pDC=GetDC();
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_LOMETRIC);
	pDC->SetWindowOrg(0,0); 
	pDC->SetViewportOrg(CPoint(rect.right / 2, rect.bottom / 2));
   
	double  x,y;
	CPoint *p=new CPoint;
	p=&point;
    pDC->DPtoLP(p); //将设备坐标转换为逻辑坐标
	x=p->x/100.0;
	y=p->y/100.0;
	//获取状态栏指针
	CStatusBar *pStatusBar=(CStatusBar*)GetParentFrame()->GetDescendantWindow(ID_VIEW_STATUS_BAR);
	if(pStatusBar)
	{
		char buf[40];
		sprintf(buf,"(%4.2f,%4.2f)",x,y);
		pStatusBar->SetPaneText(1,buf);
	}
	//创建工具提示控件
	CString  strR,strG,strB;
    COLORREF clr=pDC->GetPixel(point.x,point.y);   //获取当前鼠标点像素值
	strR.Format("%d",GetRValue(clr));              //分解出红色值
    strG.Format("%d",GetGValue(clr));              // 分解出绿色值
    strB.Format("%d",GetBValue(clr));              //分解出蓝色值
   if((strR!="255"||strG!="255"||strB!="255"))//&&(strR!="255"||strG!="255"||strB!="0")) //判断鼠标是否指在函数曲线上
    {	
		m_pToolTip = new CToolTipCtrl; 
		if(!m_pToolTip->Create(this))
		{
			TRACE("Unable To create ToolTip/n");             
            return;   
		}
		CString  str1,str2,str;
        str1.Format("%4.2f",x);
    	str2.Format("%4.2f",y);
        str="("+str1+","+str2+")";
    	if(m_pToolTip->AddTool(this,str))   //以提示方式显示当前坐标 
		{   
			TRACE("Unable to add Dialog to the tooltip/n");         
		}                   
    	m_pToolTip->Activate(TRUE); //激活工具提示控件 
   }
	CView::OnMouseMove(nFlags, point);
}

void CHuituView::OnCreateCos() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC;
	pDC=GetDC();
	CCosFunc *m=new CCosFunc;
	CSinDlg dlg;
	CLineTypeDlg typedlg;
	if(dlg.DoModal()==IDOK)
	{
		m->m_dCos_A=dlg.m_dSin_A;
		m->m_dCos_b=dlg.m_dSin_b;
		m->m_dCos_c=dlg.m_dSin_c;
		m->m_dCos_m=dlg.m_dSin_m;
		m->m_dCos_n=dlg.m_dSin_n;
		m->m_dCos_P=dlg.m_dSin_P;
		m->m_LineColor=	m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}

}

void CHuituView::OnCreateTan() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC;
	pDC=GetDC();
	CTanFunc *m=new CTanFunc;
	CTanDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m->m_dTan_A=dlg.m_dTan_A;
		m->m_nTan_b=dlg.m_nTan_b;
		m->m_dTan_m=dlg.m_dTan_m;
		m->m_dTan_n=dlg.m_dTan_n;
		m->m_LineColor=	m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;	
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}

}

BOOL CHuituView::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (NULL!=m_pToolTip)              
		m_pToolTip->RelayEvent(pMsg);  
	return CView::PreTranslateMessage(pMsg);
}

void CHuituView::OnLineType() 
{
	// TODO: Add your command handler code here
	CLineTypeDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m_LineColor=dlg.m_LineColor;
		m_nLineType=dlg.m_nLineType;
		m_nLineWidth=dlg.m_nLineWidth;
	}
}
void CHuituView::OnCreatePower()   //幂函数
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC;
	pDC=GetDC();
	CPowerFunc *m=new  CPowerFunc;
	CPowerDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m->m_da=dlg.m_da;
		m->m_dm=dlg.m_dm;
		m->m_dn=dlg.m_dn;
		m->m_LineColor=m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}
	
}

void CHuituView::OnCreateExp()   //指数函数
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC *pDC;
	pDC=GetDC();
	CExpFunc *m=new  CExpFunc;
	CExpDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m->m_da=dlg.m_da;
		m->m_dm=dlg.m_dm;
		m->m_dn=dlg.m_dn;
		m->m_LineColor=m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}
	
	
}

void CHuituView::OnButtonRed() 
{
	// TODO: Add your command handler code here
	m_LineColor=RGB(255,0,0);
}

void CHuituView::OnButtonGreen() 
{
	// TODO: Add your command handler code here
	m_LineColor=RGB(0,255,0);
}

void CHuituView::OnButtonBlue() 
{
	// TODO: Add your command handler code here
		m_LineColor=RGB(0,0,255);
}

void CHuituView::OnEnlarge() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_nMutiple++;	
	pDoc->UpdateAllViews(NULL);
}

void CHuituView::OnRecover() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_nMutiple=1;	
	pDoc->UpdateAllViews(NULL);
}

void CHuituView::OnReduce() 
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(m_nMutiple>1)
		m_nMutiple--;	
	pDoc->UpdateAllViews(NULL);
}

void CHuituView::OnCreateDouble() //二次函数
{
	// TODO: Add your command handler code here
	CHuituDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    CDC *pDC;
	pDC=GetDC();
    DoubleFunc *m=new DoubleFunc;
	CDoubleDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		m->m_da=dlg.m_da;
		m->m_db=dlg.m_db;
		m->m_dc=dlg.m_db;
		m->m_dm=dlg.m_dm;
		m->m_dn=dlg.m_dn;
		m->m_LineColor=	m_LineColor;
		m->m_nLineType=m_nLineType;
		m->m_nMutiple=m_nMutiple;
		m->m_nLineWidth=m_nLineWidth;
		m->Draw(pDC,*this);
	    pDoc->m_FigureList.AddTail(m);
	}
	
}

// LinearDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "LinearDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinearDlg dialog


CLinearDlg::CLinearDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinearDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinearDlg)
	m_dA = 0.0;
	m_dB = 0.0;
	m_dm = 0.0;
	m_dn = 0.0;
	//}}AFX_DATA_INIT
}


void CLinearDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinearDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_dA);
	DDX_Text(pDX, IDC_EDIT_B, m_dB);
	DDX_Text(pDX, IDC_EDIT_M, m_dm);
	DDX_Text(pDX, IDC_EDIT_N, m_dn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinearDlg, CDialog)
	//{{AFX_MSG_MAP(CLinearDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinearDlg message handlers

// LinearFunc.cpp: implementation of the CLinearFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "LinearFunc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLinearFunc::CLinearFunc(double A,double B,double m,double n,int mutiple,
						 int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{
	m_dA=A;
	m_dB=B;
	m_dm=m;
	m_dn=n;
}

CLinearFunc::~CLinearFunc()
{

}
void CLinearFunc::Draw(CDC *pDC,HWND hWnd)
{
	CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
    
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	int x1,y1,x2,y2;
	y1=(int)((m_dA*m_dm+m_dB)*100*m_nMutiple);
	x1=(int)(m_dm*100*m_nMutiple);
	y2=(int)((m_dA*m_dn+m_dB)*100*m_nMutiple);
	x2=(int)(m_dn*100*m_nMutiple);
	pDC->MoveTo(x1,y1);
	pDC->LineTo(x2,y2);
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
IMPLEMENT_SERIAL(CLinearFunc,CLineType,0)
void CLinearFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_dA<<m_dB<<m_dm<<m_dn;
	}
	else
	{
		ar>>m_dA>>m_dB>>m_dm>>m_dn;
	}
}

// LineType.cpp: implementation of the CLineType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "LineType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLineType::CLineType()
{
	m_nMutiple=1;
	m_nLineType=PS_SOLID;
	m_nLineWidth=1;
	m_LineColor=RGB(0,0,0);

}
CLineType::CLineType(int mutiple,int linewidth,int linetype,COLORREF linecolor)
{
	m_nMutiple=mutiple;
	m_nLineType=linetype;
	m_nLineWidth=linewidth;
	m_LineColor=linecolor;
}
CLineType::~CLineType()
{

}
void CLineType::Draw(CDC *pDC,HWND hWnd)
{

}
IMPLEMENT_SERIAL(CLineType,CObject,0)
void CLineType::Serialize(CArchive &ar)
{
	if(ar.IsStoring())
	{
		ar<<m_nMutiple<<m_nLineType<<m_nLineWidth<<m_LineColor;
	}
	else
	{
		ar>>m_nMutiple>>m_nLineType>>m_nLineWidth>>m_LineColor;
	}
}

// LineTypeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "LineTypeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLineTypeDlg dialog


CLineTypeDlg::CLineTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLineTypeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLineTypeDlg)
	m_nLineWidth = 0;
	//}}AFX_DATA_INIT
}


void CLineTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLineTypeDlg)
	DDX_Control(pDX, IDC_LIST_LINETYPE, m_List_LineType);
	DDX_Text(pDX, IDC_EDIT_LINEWIDTH, m_nLineWidth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLineTypeDlg, CDialog)
	//{{AFX_MSG_MAP(CLineTypeDlg)
	ON_BN_CLICKED(IDC_BUTTON_LINECOLOR, OnButtonLinecolor)
	ON_LBN_SELCHANGE(IDC_LIST_LINETYPE, OnSelchangeListLinetype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLineTypeDlg message handlers

void CLineTypeDlg::OnButtonLinecolor() 
{
	// TODO: Add your control notification handler code here
	CColorDialog ColorDlg;
	if(ColorDlg.DoModal()==IDOK)
	{
		m_LineColor=ColorDlg.GetColor();  //获取选择的颜色
	}
}

BOOL CLineTypeDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_List_LineType.AddString("实线");
	m_List_LineType.AddString("虚线");
	m_List_LineType.AddString("点线");
	m_List_LineType.AddString("点划线");
	m_List_LineType.AddString("双点划线");
	m_List_LineType.SetCurSel(0);
	m_nLineType=0;
	m_nLineWidth=1;
	m_LineColor=RGB(0,0,0);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLineTypeDlg::OnSelchangeListLinetype() 
{
	// TODO: Add your control notification handler code here
	int nIndex=m_List_LineType.GetCurSel();
	switch(nIndex)
	{
	case 0: m_nLineType=PS_SOLID; break;
	case 1: m_nLineType=PS_DASH; break;
	case 2: m_nLineType=PS_DOT; break;
	case 3: m_nLineType=PS_DASHDOT; break;
	case 4: m_nLineType=PS_DASHDOTDOT; break;
	default: m_nLineType=PS_SOLID;
	}
}

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Huitu.h"

#include "MainFrm.h"
#include "HuituDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_MOUSE_POS,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    cs.style&=~FWS_ADDTOTITLE;  //去除单文档前的部分
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CHuituDoc *pDoc=(CHuituDoc*)this->GetActiveDocument();
	pDoc->RemoveList();
	CFrameWnd::OnClose();
}

// PowerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "PowerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg dialog


CPowerDlg::CPowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPowerDlg)
	m_da = 0.0;
	m_dm = 0.0;
	m_dn = 0.0;
	//}}AFX_DATA_INIT
}


void CPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_da);
	DDX_Text(pDX, IDC_EDIT_M, m_dm);
	DDX_Text(pDX, IDC_EDIT_N, m_dn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPowerDlg, CDialog)
	//{{AFX_MSG_MAP(CPowerDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg message handlers

// PowerFunc.cpp: implementation of the CPowerFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "PowerFunc.h"
#include <AFXTEMPL.H>
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPowerFunc::CPowerFunc(double a,double m,double n,int mutiple,
					   int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{
	m_da=a;
	m_dm=m;
	m_dn=n;
}

CPowerFunc::~CPowerFunc()
{

}
void CPowerFunc::Draw(CDC *pDC,HWND hWnd)
{
    CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
	CString str1,str;
    str1.Format("%.2f",m_da);
	str="y=x^"+str1;
	pDC->TextOut((int)(m_dn*100*m_nMutiple),300,str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;  //模板数组
	CPoint p;
	double k;
	int i,sum;
	for(k=m_dm;k<m_dn;k+=0.1)
	{
		sum=(int)(pow(k,m_da)*100*m_nMutiple);
		p.x=(int)(k*100*m_nMutiple);
		p.y=sum;
	if(p.x<=1000&&p.x>=-1000)
			  m_Array.Add(p);
	}
	int  n=m_Array.GetSize();
	for(i=0;i<n-1;i++)   //绘制图像
	{
		pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
    pDC->SelectObject(pOldPen);
	pen.DeleteObject();

}
IMPLEMENT_SERIAL(CPowerFunc,CLineType,0)
void CPowerFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_da<<m_dm<<m_dn;
	}
	else
	{
		ar>>m_da>>m_dm>>m_dn;
	}
}

// SinDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "SinDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSinDlg dialog


CSinDlg::CSinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSinDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSinDlg)
	m_dSin_A = 0.0;
	m_dSin_b = 0.0;
	m_dSin_c = 0.0;
	m_dSin_m = 0.0;
	m_dSin_n = 0.0;
	m_dSin_P = 0.0;
	//}}AFX_DATA_INIT
}


void CSinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSinDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_dSin_A);
	DDX_Text(pDX, IDC_EDIT_B, m_dSin_b);
	DDX_Text(pDX, IDC_EDIT_C, m_dSin_c);
	DDX_Text(pDX, IDC_EDIT_M, m_dSin_m);
	DDX_Text(pDX, IDC_EDIT_N, m_dSin_n);
	DDX_Text(pDX, IDC_EDIT_P, m_dSin_P);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSinDlg, CDialog)
	//{{AFX_MSG_MAP(CSinDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinDlg message handlers

// SinFunc.cpp: implementation of the CSinFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "SinFunc.h"

#include <AFXTEMPL.H>
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSinFunc::CSinFunc(double A,double b,double c,double P,double m,double n,int mutiple,
				   int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{
	m_dSin_A=A;
	m_dSin_b=b;
	m_dSin_c=c;
	m_dSin_P=P;
	m_dSin_m=m;
	m_dSin_n=n;
}

CSinFunc::~CSinFunc()
{

}
void CSinFunc::Draw(CDC *pDC,HWND hWnd)     //绘制函数图像
{
	CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
    CString str1,str2,str3,str4,str;
    str1.Format("%.2f",m_dSin_A);
    str2.Format("%.2f",m_dSin_b);
	str3.Format("%.2f",m_dSin_c);
	str4.Format("%.2f",m_dSin_P);
	str="y="+str1+"Sin("+str2+"x"+str3+")"+"+"+str3;
	pDC->TextOut((int)(m_dSin_n*100*m_nMutiple),(int)((m_dSin_A*sin(m_dSin_b*m_dSin_n+m_dSin_c)+m_dSin_P)*100*m_nMutiple),str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;  //模板数组
	double  k;
	int sum;  
	int i;
	CPoint p;
	for(k=m_dSin_m;k<m_dSin_n;k+=0.01)   //对图像进行采样点 
	{
          sum=(int)((m_dSin_A*sin(m_dSin_b*k+m_dSin_c)+m_dSin_P)*100*m_nMutiple);
		  p.x=k*100*m_nMutiple;
		  p.y=sum;
		  if(p.x<=1000&&p.x>=-1000)
			  m_Array.Add(p);
	}
	int  n=m_Array.GetSize();
	for(i=0;i<n-1;i++)   //绘制图像
	{
		pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
    pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
IMPLEMENT_SERIAL(CSinFunc,CLineType,0)
void CSinFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_dSin_A<<m_dSin_b<<m_dSin_c<<m_dSin_P<<m_dSin_m<<m_dSin_n;
	}
	else
	{
		ar>>m_dSin_A>>m_dSin_b>>m_dSin_c>>m_dSin_P>>m_dSin_m>>m_dSin_n;
	}
}

// stdafx.cpp : source file that includes just the standard includes
//	Huitu.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TanDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Huitu.h"
#include "TanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTanDlg dialog


CTanDlg::CTanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTanDlg)
	m_dTan_A = 0.0;
	m_nTan_b = 0;
	m_dTan_m = 0.0;
	m_dTan_n = 0.0;
	//}}AFX_DATA_INIT
}


void CTanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTanDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_dTan_A);
	DDX_Text(pDX, IDC_EDIT_B, m_nTan_b);
	DDX_Text(pDX, IDC_EDIT_M, m_dTan_m);
	DDX_Text(pDX, IDC_EDIT_N, m_dTan_n);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTanDlg, CDialog)
	//{{AFX_MSG_MAP(CTanDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTanDlg message handlers

// TanFunc.cpp: implementation of the CTanFunc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Huitu.h"
#include "TanFunc.h"

#include <AFXTEMPL.H>
#include "math.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTanFunc::CTanFunc(double A,int b,double m,double n,int mutiple,
				   int linewidth,int linetype,COLORREF linecolor):CLineType(mutiple,linewidth,linetype,linecolor)
{

	m_dTan_A=A;
	m_nTan_b=b;
	m_dTan_m=m;
	m_dTan_n=n;
}

CTanFunc::~CTanFunc()
{

}
void CTanFunc::Draw(CDC *pDC,HWND hWnd)  //绘制图像   y=Atan(b*x)
{
	CRect rect;     
	GetClientRect(hWnd,rect);       //获取客户区窗口大小
	pDC->SetMapMode(MM_LOMETRIC);   //设置映射模式
	pDC->SetWindowOrg(0,0);         //平移逻辑坐标系原点的操作
	pDC->SetViewportOrg(CPoint(rect.right/2,rect.bottom/2));   //平移设备坐标系原点的操作
    CString str1,str2,str;
    str1.Format("%.2f",m_dTan_A);
    str2.Format("%.2f",m_nTan_b);
	str="y="+str1+"Tan("+str2+"x"+")";
	pDC->TextOut((int)(m_dTan_n*100*m_nMutiple),(int)(m_dTan_A*tan(m_dTan_n*m_nTan_b)*100*m_nMutiple),str);
	CPen pen(m_nLineType,m_nLineWidth,m_LineColor); //生成新画笔
	CPen *pOldPen = pDC->SelectObject(&pen);        //保存旧画笔
	CArray<CPoint,CPoint&> m_Array;  //模板数组
	int i;
	double k;
	int sum;
	//int  period=(int)(3.14159/m_nTan_b*100);
	CPoint p;
	for(k=m_dTan_m;k<m_dTan_n;k+=0.01)
	{
		sum=(int)(m_dTan_A*tan(k*m_nTan_b)*100*m_nMutiple);
		p.x=k*100*m_nMutiple;
		p.y=sum;
		if(p.x<=1000&&p.x>=-1000)
			m_Array.Add(p);
	}
/*
	CPen pen1(PS_DOT, 1, RGB(100, 100, 100));
	CPen *pOldPen = pDC->SelectObject(&pen1);
    for(i=0;i<9;i++)
	{
		pDC->MoveTo(period/2+i*period,500);
		pDC->LineTo(period/2+i*period,-500);
	}
	for(i=0;i>-9;i--)
	{
		pDC->MoveTo(-period/2+i*period,500);
		pDC->LineTo(-period/2+i*period,-500);
	}
	pDC->SelectObject(pOldPen);
	pen1.DeleteObject();
*/

    int n=m_Array.GetSize();
	for(i=0;i<n-1;i++)     //绘制图形
	{
    	pDC->MoveTo(m_Array.GetAt(i));
	    pDC->LineTo(m_Array.GetAt(i+1));
	}
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
}
IMPLEMENT_SERIAL(CTanFunc,CLineType,0)
void CTanFunc::Serialize(CArchive &ar)
{
	CLineType::Serialize(ar);
	if(ar.IsStoring())
	{
		ar<<m_dTan_A<<m_nTan_b<<m_dTan_m<<m_dTan_n;
	}
	else
	{
		ar>>m_dTan_A>>m_nTan_b>>m_dTan_m>>m_dTan_n;
	}

}
