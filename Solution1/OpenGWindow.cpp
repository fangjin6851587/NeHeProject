//#define DEFAULT
//#define EXAMPLE1
//#define EXAMPLE2
//#define EXAMPLE3
//#define EXAMPLE4
#define EXAMPLE5
//#define EXAMPLE6

#include <windows.h>
#include <gl/glew.h>
#include <gl/GLUT.H>
#include "ExampleBase.h"
#include "GlobalExampleDefine.h"

#ifdef EXAMPLE1
#include "Example1.h"
#endif
#ifdef EXAMPLE2
#include "Example2.h"
#endif
#ifdef EXAMPLE3
#include "Example3.h"
#endif
#ifdef EXAMPLE4
#include "Example4.h"
#endif

#ifdef EXAMPLE5
#include "Example5.h"
#endif

#ifdef EXAMPLE6
#include "Example6.h"
#endif

HGLRC hrc = NULL;
HDC hdc = NULL;
HWND hwnd = NULL;
HINSTANCE hInstance;
bool active = TRUE;
bool fullscreen = TRUE;
ExampleBase* example = NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
}

int InitGL(GLvoid)
{
#ifdef EXAMPLE1
	example = new Example1();
#endif // EXAMPLE1
#ifdef EXAMPLE2
	example = new Example2();
#endif
#ifdef EXAMPLE3
	example = new Example3();
#endif
#ifdef EXAMPLE4
	example = new Example4();
#endif
#ifdef EXAMPLE5
	example = new Example5();
#endif
#ifdef EXAMPLE6
	example = new Example6();
#endif
	if(example)
		return example->InitGL();
	return FALSE;
}

int DrawGLScene(GLvoid)
{
	if (example)
		return example->DrawGLScene();
	return FALSE;
}

GLvoid KillGLWindow(GLvoid)
{
	if (fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);

		ShowCursor(TRUE);
	}

	if (hrc)
	{
		if (!wglMakeCurrent(NULL, NULL))
		{
			MessageBox(NULL, "Spawn DC or RC failed.", "Ok", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hrc))
		{
			MessageBox(NULL, "Spawn RC failed.", "Ok", MB_OK | MB_ICONINFORMATION);
		}
		hrc = NULL;
	}

	if (hdc && !ReleaseDC(hwnd, hdc))
	{
		MessageBox(NULL, "Spawn DC failed.", "Ok", MB_OK | MB_ICONINFORMATION);
		hdc = NULL;
	}

	if (hwnd && !DestroyWindow(hwnd))
	{
		MessageBox(NULL, "Spawn HWND failed.", "Ok", MB_OK | MB_ICONINFORMATION);
		hwnd = NULL;
	}

	if (!UnregisterClass("OpenG", hInstance))
	{
		MessageBox(NULL, "Unregister HINSTANCE failed.", "Ok", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint PixelFormat;

	WNDCLASS wc;

	DWORD dwExStyle;

	DWORD dwStyle;

	RECT WindowRect;

	WindowRect.left = (LONG)0;

	WindowRect.right = (LONG)width;

	WindowRect.top = (LONG)0;

	WindowRect.bottom = (LONG)height;

	fullscreen = fullscreenflag;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	wc.lpfnWndProc = (WNDPROC)WndProc;

	wc.cbWndExtra = 0;

	wc.cbClsExtra = 0;

	wc.hInstance = hInstance;

	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = NULL;

	wc.lpszMenuName = NULL;

	wc.lpszClassName = "OpenG";

	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Register WNDCLASS failed", "Error", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (fullscreen)
	{
		DEVMODE dmScreenSettings;

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));			// 确保内存清空为零

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Devmode 结构的大小

		dmScreenSettings.dmPelsWidth = width;				// 所选屏幕宽度

		dmScreenSettings.dmPelsHeight = height;				// 所选屏幕高度

		dmScreenSettings.dmBitsPerPel = bits;					// 每象素所选的色彩深度

		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "FullScreen setting failed in current GPU!\n set window model？", "NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;
			}
			else
			{
				MessageBox(NULL, "Program will close", "Error", MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (fullscreen)								// 仍处于全屏模式吗?
	{
		dwExStyle = WS_EX_APPWINDOW;					// 扩展窗体风格

		dwStyle = WS_POPUP;						// 窗体风格

		ShowCursor(FALSE);						// 隐藏鼠标指针
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// 扩展窗体风格

		dwStyle = WS_OVERLAPPEDWINDOW;					//  窗体风格

	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// 调整窗口达到真正要求的大小

	if (!(hwnd = CreateWindowEx(dwExStyle,				// 扩展窗体风格

		"OpenG",				// 类名字

		title,					// 窗口标题

		WS_CLIPSIBLINGS |			// 必须的窗体风格属性

		WS_CLIPCHILDREN |			// 必须的窗体风格属性

		dwStyle,				// 选择的窗体属性

		0, 0,					// 窗口位置

		WindowRect.right - WindowRect.left,	// 计算调整好的窗口宽度

		WindowRect.bottom - WindowRect.top,	// 计算调整好的窗口高度

		NULL,					// 无父窗口

		NULL,					// 无菜单

		hInstance,				// 实例

		NULL)))					// 不向WM_CREATE传递任何东东
	{
		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "CreateWindowEx failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =					// /pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式

	{

		sizeof(PIXELFORMATDESCRIPTOR),					// 上述格式描述符的大小

		1,								// 版本号

		PFD_DRAW_TO_WINDOW |						// 格式支持窗口

		PFD_SUPPORT_OPENGL |						// 格式必须支持OpenGL

		PFD_DOUBLEBUFFER,						// 必须支持双缓冲

		PFD_TYPE_RGBA,							// 申请 RGBA 格式

		bits,								// 选定色彩深度

		0, 0, 0, 0, 0, 0,						// 忽略的色彩位

		0,								// 无Alpha缓存

		0,								// 忽略Shift Bit

		0,								// 无累加缓存

		0, 0, 0, 0,							// 忽略聚集位

		16,								// 16位 Z-缓存 (深度缓存)

		0,								// 无蒙板缓存

		0,								// 无辅助缓存

		PFD_MAIN_PLANE,							// 主绘图层

		0,								// Reserved

		0, 0, 0								// 忽略层遮罩

	};

	if (!(hdc = GetDC(hwnd)))							// 取得设备描述表了么?

	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "GetDC Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE

	}

	if (!(PixelFormat = ChoosePixelFormat(hdc, &pfd)))				// Windows 找到相应的象素格式了吗?
	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "ChoosePixelFormat Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE
	}

	if (!SetPixelFormat(hdc, PixelFormat, &pfd))				// 能够设置象素格式么?
	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "SetPixelFormat Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE
	}

	if (!(hrc = wglCreateContext(hdc)))					// 能否取得着色描述表?
	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "wglCreateContext Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE
	}

	if (!wglMakeCurrent(hdc, hrc))						// 尝试激活着色描述表
	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "wglMakeCurrent", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE

	}

	ShowWindow(hwnd, SW_SHOW);						// 显示窗口

	SetForegroundWindow(hwnd);						// 略略提高优先级

	SetFocus(hwnd);								// 设置键盘的焦点至此窗口

	ReSizeGLScene(width, height);						// 设置透视 GL 屏幕

	if (!InitGL())								// 初始化新建的GL窗口
	{

		KillGLWindow();							// 重置显示区

		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// 返回 FALSE
	}


	return TRUE;
}

LRESULT CALLBACK WndProc(HWND	hWnd,					// 窗口的句柄

	UINT	uMsg,					// 窗口的消息

	WPARAM	wParam,					// 附加的消息内容

	LPARAM	lParam)					// 附加的消息内容
{
	switch (uMsg)								// 检查Windows消息
	{
	case WM_ACTIVATE:						// 监视窗口激活消息
	{
		if (!HIWORD(wParam))					// 检查最小化状态
		{
			active = TRUE;					// 程序处于激活状态
		}
		else
		{
			active = FALSE;					// 程序不再激活
		}
		return 0;						// 返回消息循环
	}
	case WM_SYSCOMMAND:						// 系统中断命令
	{
		switch (wParam)						// 检查系统调用
		{
		case SC_SCREENSAVE:				// 屏保要运行?
		case SC_MONITORPOWER:				// 显示器要进入节电模式?
			return 0;					// 阻止发生
		}
		break;							// 退出
	}
	case WM_CLOSE:							// 收到Close消息?
	{
		PostQuitMessage(0);					// 发出退出消息
		return 0;						// 返回
	}
	case WM_KEYDOWN:						// 有键按下么?
	{
		keys[wParam] = TRUE;					// 如果是，设为TRUE
		return 0;						// 返回
	}
	case WM_KEYUP:							// 有键放开么?
	{
		keys[wParam] = FALSE;					// 如果是，设为FALSE
		return 0;						// 返回
	}
	case WM_SIZE:							// 调整OpenGL窗口大小
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));		// LoWord=Width,HiWord=Height
		return 0;						// 返回
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,				// 当前窗口实例
	HINSTANCE	hPrevInstance,				// 前一个窗口实例
	LPSTR		lpCmdLine,				// 命令行参数
	int		nCmdShow)				// 窗口显示状态
{
	MSG	msg;								// Windowsx消息结构

	BOOL	done = FALSE;							// 用来退出循环的Bool 变量

	if (MessageBox(NULL, "FullScreen Modle？", "Set FullScreen", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;						// FALSE为窗口模式
	}

	if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
	{
		return 0;							// 失败退出
	}

	while (!done)								// 保持循环直到 done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))			// 有消息在等待吗?
		{
			if (msg.message == WM_QUIT)				// 收到退出消息?
			{
				done = TRUE;					// 是，则done=TRUE
			}
			else							// 不是，处理窗口消息
			{
				TranslateMessage(&msg);				// 翻译消息
				DispatchMessage(&msg);				// 发送消息
			}
		}
		else
		{
			if (active)						// 程序激活的么?
			{
				if (keys[VK_ESCAPE])				// ESC 按下了么?
				{
					done = TRUE;				// ESC 发出退出信号
				}
				else						// 不是退出的时候，刷新屏幕
				{
					DrawGLScene();				// 绘制场景
					SwapBuffers(hdc);			// 交换缓存 (双缓存)
					if (example)
					{
						example->DoKeysAction();
					}
				}
			}

			if (keys[VK_F1])					// F1键按下了么?
			{
				keys[VK_F1] = FALSE;				// 若是，使对应的Key数组中的值为 FALSE
				KillGLWindow();					// 销毁当前的窗口
				fullscreen = !fullscreen;				// 切换 全屏 / 窗口 模式
				// 重建 OpenGL 窗口

#ifdef DEFAULT
				if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
				{
					return 0;				
				}
#else
				if (example && !CreateGLWindow(example->GetGLWindowTitle(), 640, 480, 16, fullscreen))
				{
					return 0;				// 如果窗口未能创建，程序退出
				}
#endif
			}
		}
	}

	KillGLWindow();								// 销毁窗口

	return (msg.wParam);							// 退出程序
}