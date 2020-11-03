
// GraffitiGdiPluaaaas.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号


// CGraffitiGdiPluaaaasApp:
// 有关此类的实现，请参阅 GraffitiGdiPluaaaas.cpp


/*Status GdiplusStarup	//gdi启动函数//不用自己写。。。。。。
(
	OUT ULONG_PTR* token,					//GdiplusShutdown 要用
	const GdiplusStartupInput* input,	    //结构体指针
	OUT GdiplusStartupOutput* output		//结构体指针取NULL
);
void GdiplusShutdown(ULONG_PTR token);*/

class CGraffitiGdiPluaaaasApp : public CWinApp
{
public:
	CGraffitiGdiPluaaaasApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
	// 不知道做什么的成员变量
	GdiplusStartupInput GdiInput;
	ULONG_PTR GdiToken;
	// 照抄的函数（gdip准备工作）
	int ExitInstance();
};

extern CGraffitiGdiPluaaaasApp theApp;
