
// GraffitiGdiPluaaaasDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "GraffitiGdiPluaaaas.h"
#include "GraffitiGdiPluaaaasDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGraffitiGdiPluaaaasDlg 对话框



CGraffitiGdiPluaaaasDlg::CGraffitiGdiPluaaaasDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GRAFFITIGDIPLUAAAAS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGraffitiGdiPluaaaasDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGraffitiGdiPluaaaasDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_LINE, &CGraffitiGdiPluaaaasDlg::OnLine)
	ON_COMMAND(ID_LINES, &CGraffitiGdiPluaaaasDlg::OnLines)
	ON_COMMAND(ID_CRUVE, &CGraffitiGdiPluaaaasDlg::OnCruve)
END_MESSAGE_MAP()


// CGraffitiGdiPluaaaasDlg 消息处理程序

BOOL CGraffitiGdiPluaaaasDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CRect rect;//定义一个区域
	picDC = GetDlgItem(IDC_STATIC_PIC)->GetDC();//返回设备：类CDC*//绑定
	GetDlgItem(IDC_STATIC_PIC)->GetClientRect(&rect);
	//将控件绑定到区域。以后可以直接调用这个区域
	picClient_W = rect.Width();
	picClient_H = rect.Height();
	CenterX = rect.CenterPoint().x;
	CenterY = rect.CenterPoint().y;
	//创建共用图形对象
	//graph =::new Graphics(picDC->m_hDC);//debug下，用debug new取代了new
	graph = Graphics::FromHDC(picDC->m_hDC);//同上
	int ColorVal = GetSysColor(COLOR_BTNFACE);
	char red = GetRValue(ColorVal);
	char green = GetGValue(ColorVal);
	BYTE blue = GetBValue(ColorVal);
	int alpha = 255;//不透明
	BkColor = Color(alpha, red, green, blue);//不透明：可以缺省

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGraffitiGdiPluaaaasDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGraffitiGdiPluaaaasDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGraffitiGdiPluaaaasDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//画直线
void CGraffitiGdiPluaaaasDlg::OnLine()
{
	// TODO: 在此添加命令处理程序代码
	//Invalidate();			//窗口客户区无效？？？？？？？什么意思
	//UpdateWindow();		//更新客户区窗口
	graph->Clear(BkColor);	//GDI+新整的函数，取代上面两行
	int alpha = 255;
	Pen myPen(Color(alpha, 255, 0, 0), 3);	//红笔，宽3
	Point P1(100, 150);	//坐标原点：左上角
	Point P2(300, 50);
	graph->DrawLine(&myPen, P1, P2);
}

//画折线
void CGraffitiGdiPluaaaasDlg::OnLines()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);								//清除区域
	Pen myPen(Color(0, 0, 255), 2);						//设置两个宽度的蓝钢笔
	Point point[4] = {	Point(30,230),Point(150,200),	//设置点数组
						Point(200,40),Point(350,70) };
	graph->DrawLines(&myPen, point, 4);
	//调用区域的画折线行数，传入pen地址，以及点地址，以及点的个数		
}

//画曲线
void CGraffitiGdiPluaaaasDlg::OnCruve()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);
	Pen bluePen(Color::Blue, 2);//use the defaut colors
	bluePen.SetDashStyle(DashStyleDash);//??
	Pen redPen(Color::Red, 2);
	redPen.SetDashStyle(DashStyleDot);//点线
	Pen BlackPen(Color::Black);
	Point point1(30, 230); Point point2(150, 200);
	Point point3(200, 40); Point point4(350, 70);
	Point Points[4] = { point1,point2,point3,point4 };
	graph->DrawCurve(&bluePen, Points, 4, 0.0);//0:直线（张力）
	graph->DrawCurve(&redPen, Points, 4, 0.5);//0.5:缺省值
	graph->DrawCurve(&BlackPen, Points, 4, 1);//1:最弯
}
