
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
	ON_COMMAND(ID_CLOSEDCRUVE, &CGraffitiGdiPluaaaasDlg::OnClosedcruve)
	ON_COMMAND(ID_RECTANGLE, &CGraffitiGdiPluaaaasDlg::OnRectangle)
	ON_COMMAND(ID_ELLIPSE, &CGraffitiGdiPluaaaasDlg::OnEllipse)
	ON_COMMAND(ID_ARC, &CGraffitiGdiPluaaaasDlg::OnArc)
	ON_COMMAND(ID_PIE, &CGraffitiGdiPluaaaasDlg::OnPie)
	ON_COMMAND(ID_POLYGON, &CGraffitiGdiPluaaaasDlg::OnPolygon)
	ON_COMMAND(ID_FILL_RECTANGLE, &CGraffitiGdiPluaaaasDlg::OnFillRectangle)
	ON_COMMAND(ID_FILL_ELLIPSE, &CGraffitiGdiPluaaaasDlg::OnFillEllipse)
	ON_COMMAND(ID_FILL_POLYGON, &CGraffitiGdiPluaaaasDlg::OnFillPolygon)
	ON_COMMAND(ID_MULTIDRAWLINE, &CGraffitiGdiPluaaaasDlg::OnMultidrawline)
	ON_COMMAND(ID_DRAW_STRING, &CGraffitiGdiPluaaaasDlg::OnDrawString)
	ON_COMMAND(ID_HATCH_BRUSH, &CGraffitiGdiPluaaaasDlg::OnHatchBrush)
	ON_COMMAND(ID_TEXTURE_BRUSH, &CGraffitiGdiPluaaaasDlg::OnTextureBrush)
	ON_COMMAND(ID_LINER_GRADIENT_BRUSH, &CGraffitiGdiPluaaaasDlg::OnLinerGradientBrush)
	ON_COMMAND(ID_TUANSLATE_TRANSFORM, &CGraffitiGdiPluaaaasDlg::OnTuanslateTransform)
	ON_COMMAND(ID_ROTATE_TRANSFORM, &CGraffitiGdiPluaaaasDlg::OnRotateTransform)
	ON_COMMAND(ID_SCALE_TRANSFORM_1, &CGraffitiGdiPluaaaasDlg::OnScaleTransform1)
	ON_COMMAND(ID_SCALE_TRANSFORM, &CGraffitiGdiPluaaaasDlg::OnScaleTransform)
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
	//Invalidate();			//窗口客户区无效//为了刷新
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
	bluePen.SetDashStyle(DashStyleDash);//虚线
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

//笛卡尔曲线
void CGraffitiGdiPluaaaasDlg::OnClosedcruve()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);//用白色清除客户区
	Point point1(30, 230);
	Point point2(150, 200);
	Point point3(200, 40);
	Point point4(350, 70);
	Point Points[4] = { point1,point2,point3,point4 };
	Pen redPen(Color::Red, 2);//选择画笔
	graph->DrawClosedCurve(&redPen, Points, 4, 0.5);//最后一个参数：张力
	
}

//矩形
void CGraffitiGdiPluaaaasDlg::OnRectangle()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	Pen myPen(Color::Magenta, 2);	//品红
	Rect rect(70, 40, 250, 120);	//x,y位置；with，high大小
	graph->DrawRectangle(&myPen, rect);
}

//椭圆
void CGraffitiGdiPluaaaasDlg::OnEllipse()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);		//重绘
	Pen myPen(Color::Magenta, 2);
	Rect rect(70, 40, 250, 120);	//外接矩形
	graph->DrawEllipse(&myPen, rect);//画椭圆
	Pen myPen2(Color::DarkMagenta, 1);//定义暗品红（pen2）
	myPen2.SetDashStyle(DashStyleDash);//虚线（pen2）
	graph->DrawRectangle(&myPen2, rect);//画矩形
}

//弧
void CGraffitiGdiPluaaaasDlg::OnArc()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	Pen myPen(Color::Magenta, 2);	//品红
	Rect rect(50, 50, 250, 150);	//弧的外接矩形
	float startAngle = -30;	//弧的开始∠角度
	float sweepAngle = 270;	//弧的扫掠角度
	//角度的单位是度，而非弧度。零度为x轴正方向，顺时针为正方向
	graph->DrawArc(&myPen, rect, startAngle, sweepAngle);	//绘制弧
}

//饼图
void CGraffitiGdiPluaaaasDlg::OnPie()
{
	// TODO: 在此添加命令处理程序代码
	graph -> Clear(BkColor);
	Rect rect(50, 50, 250, 150);
	float startAngle = -30;	//开始角
	float sweepAngle = 270;	//扫掠角
	Pen myPen(Color::Magenta, 2);//品红
	graph->DrawPie(&myPen, rect, startAngle, sweepAngle);//画饼图
}

//多边形（封闭）
void CGraffitiGdiPluaaaasDlg::OnPolygon()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);
	Point point1(200, 0);
	Point point2(295, 69);
	Point point3(259, 181);
	Point point4(141, 181);
	Point point5(105, 69);
	Point points1[5] = { point1 ,point2,point3,point4,point5 };
	Point points2[5] = { point1 ,point3 ,point5 ,point2 ,point4 };
	Pen myPen1(Color::Magenta, 2);
	graph->DrawPolygon(&myPen1, points1, 5);//画五边形
	Pen myPen2(Color::Green, 1);
	graph->DrawPolygon(&myPen2, points2, 5);//五角星
}

//填充矩形
void CGraffitiGdiPluaaaasDlg::OnFillRectangle()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	SolidBrush myBrush(Color::LightGreen);//单色
	Rect rect(70, 40, 250, 120);
	graph->FillRectangle(&myBrush, rect);
}


void CGraffitiGdiPluaaaasDlg::OnFillEllipse()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	Color fgColor = Color::Red;					//画刷前景色
	Color bkColor = Color::Yellow;				//画刷背景色
	HatchStyle Style = HatchStyleDivot;			//图案样式
	HatchBrush myBrush(Style, fgColor, bkColor);//图案画刷
	Rect rect(70, 40, 250, 120);				//外接矩形
	graph->FillEllipse(&myBrush, rect);
}


void CGraffitiGdiPluaaaasDlg::OnFillPolygon()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	CString filename = TEXT("红楼.png");	//缺省路径：当前目录
	Image img(filename);					//缺省图像
	WrapMode Mode = WrapModeTile;			//缺省：平铺（枚举常量）
	TextureBrush myBrush(&img/*,Mode*/);	//图像画刷
	Point points[8] =						//???
	{
		Point(picClient_W * 4 / 5,0),
		Point(picClient_W * 1 / 5,0),
		Point(0,picClient_H * 1 / 4),
		Point(0,picClient_H * 3 / 4),
		Point(picClient_W * 1 / 5, picClient_H),
		Point(picClient_W * 4 / 5,picClient_H),
		Point(picClient_W, picClient_H * 3 / 4),
		Point(picClient_W, picClient_H * 1 / 4)
	};
	graph->FillPolygon(&myBrush, points, 8);//纹理（画刷）填充多边形（平铺）
}


void CGraffitiGdiPluaaaasDlg::OnMultidrawline()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	Pen bluePen(Color(255, 0, 0, 255));//蓝笔
	Pen redPen(Color(255, 255, 0, 0));//红笔
	int x, y, alpha;//透明水平渐变，填满客户区
	for (x = 0,alpha=0; x < picClient_W; x++)//绿色线条背景
	{
		if (x % 3 == 0)alpha++;//隔行：picClient_H>255
		Pen pen(Color(alpha, 0, 255, 0));
		graph->DrawLine(&pen, x, 0, x, picClient_H);
	}
	for (x = 0, y = picClient_H; x < picClient_W; x += 10, y -= 7)
		//绘蓝线：从下向上、从左向右
	{
		graph->DrawLine(&bluePen, 0, y, x, 0);
	}
	for (x = 0, y = picClient_H; x < picClient_W; x += 5, y -= 5)
	{
		graph->DrawLine(&redPen, picClient_W, y, x, picClient_H);
	}
}


void CGraffitiGdiPluaaaasDlg::OnDrawString()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor); 
	Pen myPen(Color::Black, 1);
	RectF rect(70, 40, 280, 120);//裁剪矩形∶绘制文字范围
	graph->DrawRectangle(&myPen, rect);//画矩形框
	//-----------------—--设置字体与对齐
	CString str("落霞与孤鹜齐飞秋水共长天一色"); 
	int len = str.GetLength();
	Gdiplus::Font font(_T("黑体"),18);			//多种字体和风格
	StringFormat format;//缺省∶左到右水平输出、自动换行
						//多种格式∶方向、裁剪、换行、对齐等等
	//StringFormat format(StringFormatFlagsDirectionVertical);
	StringAlignment hsa=StringAlignmentCenter;	//中心对齐
	StringAlignment vsa=StringAlignmentCenter;
	format.SetAlignment(hsa);					//水平对齐∶行文字居中
	format.SetLineAlignment(vsa);				//垂直对齐∶行居中
	SolidBrush myBrush(Color::Red);				//实体画刷

	graph->DrawString(str, len, &font, rect, &format, &myBrush);
}

//图案
void CGraffitiGdiPluaaaasDlg::OnHatchBrush()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	CString str = L"图案啊";
	Gdiplus::Font font(L"隶书", 100);
	HatchBrush Brush1(HatchStyleForwardDiagonal, Color::Yellow, Color::Brown); 
	graph->DrawString(str, str.GetLength(), &font, PointF(0, 0), &Brush1);
	HatchBrush Brush2(HatchStyleSmallCheckerBoard, Color::Red, Color::Yellow);

	graph->DrawString(str, str.GetLength(), &font, PointF(0, 130), &Brush2);
}

//纹理
void CGraffitiGdiPluaaaasDlg::OnTextureBrush()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	CString str = L"纹理啊";
	Gdiplus::Font font(L"隶书", 100);
	CString filename = TEXT("红楼.png");
	Image img(filename);//项目文件夹里面的图像文件
	WrapMode Mode = WrapModeTile;	//枚举常量：平铺
	TextureBrush Brush(&img/*,Mode*/);

	graph->DrawString(str, str.GetLength(), &font, PointF(0, 0), &Brush);
}


void CGraffitiGdiPluaaaasDlg::OnLinerGradientBrush()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(BkColor);
	CString str = L"渐变咯";
	Gdiplus::Font font(L"仿宋", 70);
	Point p1(20, 0), p2(picClient_W - 20, 0);//两点y=0
	Color col1(Color::Red), col2(Color::Yellow);//渐变点颜色
	LinearGradientBrush myBrush(p1, p2, col1, col2);//p1(red)->p2(yellow)
	graph->DrawString(str, str.GetLength(), &font, PointF(0, 0), &myBrush);
	//多点渐变------------------------------------
	Color cols[8] =
	{
		Color::Red,Color::Orange,
		Color::Yellow,Color::Green,
		Color::Cyan, Color::Blue,
		Color::Purple, Color::Magenta
	};
	//两点之间颜色值，默认线性插值（可用SetBlend...系列函数改变)
	REAL bps[8] = { 0.0,0.15,0.3,0.45,0.6,0.75,0.875,1.0 };//渐变点
		// bps∶混色位置百分比，首尾须为O和1[中间值递增]
	myBrush.SetInterpolationColors(cols, bps, 8);//绑定渐变点颜色
	graph->DrawString(str, str.GetLength(), &font, PointF(0, 120), &myBrush);

}


void CGraffitiGdiPluaaaasDlg::OnTuanslateTransform()
{
	// TODO: 在此添加命令处理程序代码
	//GDI+∶坐标系变换（图形本身大小、位置等不变），后同graph->Clear(ColorWhite);
	Rect rectSquare(40, 30, 100, 100);//绘制矩形
	Rect rectCircle(220, 30, 100, 100);//圆的外接矩形绘圆和椭圆
	Pen BluePen(Color::Blue,2);
	Pen RedPen(Color::Red, 2);
	graph->DrawRectangle(&BluePen, rectSquare);
	graph -> DrawEllipse(&BluePen, rectCircle);
	//平移坐标系：
	graph->TranslateTransform(60, 30);//正值︰x右移, y下移
	//：平移
	graph->DrawRectangle(&RedPen, rectSquare);
	graph->DrawEllipse(&RedPen, rectCircle);
	graph->ResetTransform(); //还原坐标系（以后用)
	//graph->TranslateTransform(-60, -30);//还原坐标系（以后用)
}


void CGraffitiGdiPluaaaasDlg::OnRotateTransform()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);
	SolidBrush Brush(Color::Red);
	Gdiplus::Font font(L"华文彩云",16); 
	StringFormat Fmt;
	Fmt.SetLineAlignment(StringAlignmentCenter);//垂直对齐
	graph->TranslateTransform(float(CenterX), float(CenterY));//坐标系平移
	CString str("旋转文本");
	int len=str.GetLength();
	PointF LeftTop(10.0, -40.0);//文字左上角，改为(20.0,0.O)测试
	for(int i=0; i<360; i+=45)
	{ 
		graph->RotateTransform(float(i));//旋转坐标系（顺时针为正)
		graph->DrawString(str, len, &font, LeftTop, &Fmt,&Brush);
		graph->RotateTransform(float(-i));//还原坐标系 !!!
		//graph->ResetTransform();
	}
	/*for(int i=O; i<9; i++){
	lgraph->RotateTransform(float(30));//旋转坐标系
	graph->DrawString(str, len, &font, LeftTop, &Fmt, &Brush);}*/
	graph->ResetTransform();//坐标系还原
}


void CGraffitiGdiPluaaaasDlg::OnScaleTransform1()
{
	// TODO: 在此添加命令处理程序代码
	graph->Clear(Color::White);
	Image img(L"红楼.png");
	int imgW=img.GetWidth();
	graph->DrawImage(&img, PointF(0,0));

	float ratioX = 0.5;	//x向缩放比例
	float ratioY = 0.5; // y向缩放比例（测试两者不同的效果)
	graph->ScaleTransform(ratioX, ratioY);

	graph->DrawImage(&img, PointF(imgW / ratioX + imgW, 0));//???
	graph->ResetTransform();
}




void CGraffitiGdiPluaaaasDlg::OnScaleTransform()
{
	// TODO: 在此添加命令处理程序代码

	//图片太大了，把坐标系变变
	float ratioX = 0.5;	//x向缩放比例
	float ratioY = 0.5; // y向缩放比例
	graph->ScaleTransform(ratioX, ratioY);

	graph->Clear(Color::White);
	Image img(L"红楼.png");//项目文件夹里的图像文件
	int imgW=img.GetWidth();
	graph->DrawImage(&img, PointF(0, 0));//原图
	ratioX = -1;//x向缩放比例
	ratioY = 1; //y向缩放比例
	//graph->TranslateTransform(imgW * 4, O);//先平移(+)
	graph->ScaleTransform(ratioX, ratioY);//缩放
	graph->TranslateTransform(float(-imgW * 3), 0); //后平移(-)//？？？
	graph->DrawImage(&img, PointF(0,0));//镜像
	graph->ResetTransform();
}
