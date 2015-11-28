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

		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));			// ȷ���ڴ����Ϊ��

		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Devmode �ṹ�Ĵ�С

		dmScreenSettings.dmPelsWidth = width;				// ��ѡ��Ļ���

		dmScreenSettings.dmPelsHeight = height;				// ��ѡ��Ļ�߶�

		dmScreenSettings.dmBitsPerPel = bits;					// ÿ������ѡ��ɫ�����

		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			if (MessageBox(NULL, "FullScreen setting failed in current GPU!\n set window model��", "NeHe G", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
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

	if (fullscreen)								// �Դ���ȫ��ģʽ��?
	{
		dwExStyle = WS_EX_APPWINDOW;					// ��չ������

		dwStyle = WS_POPUP;						// ������

		ShowCursor(FALSE);						// �������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// ��չ������

		dwStyle = WS_OVERLAPPEDWINDOW;					//  ������

	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// �������ڴﵽ����Ҫ��Ĵ�С

	if (!(hwnd = CreateWindowEx(dwExStyle,				// ��չ������

		"OpenG",				// ������

		title,					// ���ڱ���

		WS_CLIPSIBLINGS |			// ����Ĵ���������

		WS_CLIPCHILDREN |			// ����Ĵ���������

		dwStyle,				// ѡ��Ĵ�������

		0, 0,					// ����λ��

		WindowRect.right - WindowRect.left,	// ��������õĴ��ڿ��

		WindowRect.bottom - WindowRect.top,	// ��������õĴ��ڸ߶�

		NULL,					// �޸�����

		NULL,					// �޲˵�

		hInstance,				// ʵ��

		NULL)))					// ����WM_CREATE�����κζ���
	{
		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "CreateWindowEx failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =					// /pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ

	{

		sizeof(PIXELFORMATDESCRIPTOR),					// ������ʽ�������Ĵ�С

		1,								// �汾��

		PFD_DRAW_TO_WINDOW |						// ��ʽ֧�ִ���

		PFD_SUPPORT_OPENGL |						// ��ʽ����֧��OpenGL

		PFD_DOUBLEBUFFER,						// ����֧��˫����

		PFD_TYPE_RGBA,							// ���� RGBA ��ʽ

		bits,								// ѡ��ɫ�����

		0, 0, 0, 0, 0, 0,						// ���Ե�ɫ��λ

		0,								// ��Alpha����

		0,								// ����Shift Bit

		0,								// ���ۼӻ���

		0, 0, 0, 0,							// ���Ծۼ�λ

		16,								// 16λ Z-���� (��Ȼ���)

		0,								// ���ɰ建��

		0,								// �޸�������

		PFD_MAIN_PLANE,							// ����ͼ��

		0,								// Reserved

		0, 0, 0								// ���Բ�����

	};

	if (!(hdc = GetDC(hwnd)))							// ȡ���豸��������ô?

	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "GetDC Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE

	}

	if (!(PixelFormat = ChoosePixelFormat(hdc, &pfd)))				// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "ChoosePixelFormat Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE
	}

	if (!SetPixelFormat(hdc, PixelFormat, &pfd))				// �ܹ��������ظ�ʽô?
	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "SetPixelFormat Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE
	}

	if (!(hrc = wglCreateContext(hdc)))					// �ܷ�ȡ����ɫ������?
	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "wglCreateContext Failed", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE
	}

	if (!wglMakeCurrent(hdc, hrc))						// ���Լ�����ɫ������
	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "wglMakeCurrent", "Error", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE

	}

	ShowWindow(hwnd, SW_SHOW);						// ��ʾ����

	SetForegroundWindow(hwnd);						// ����������ȼ�

	SetFocus(hwnd);								// ���ü��̵Ľ������˴���

	ReSizeGLScene(width, height);						// ����͸�� GL ��Ļ

	if (!InitGL())								// ��ʼ���½���GL����
	{

		KillGLWindow();							// ������ʾ��

		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);

		return FALSE;							// ���� FALSE
	}


	return TRUE;
}

LRESULT CALLBACK WndProc(HWND	hWnd,					// ���ڵľ��

	UINT	uMsg,					// ���ڵ���Ϣ

	WPARAM	wParam,					// ���ӵ���Ϣ����

	LPARAM	lParam)					// ���ӵ���Ϣ����
{
	switch (uMsg)								// ���Windows��Ϣ
	{
	case WM_ACTIVATE:						// ���Ӵ��ڼ�����Ϣ
	{
		if (!HIWORD(wParam))					// �����С��״̬
		{
			active = TRUE;					// �����ڼ���״̬
		}
		else
		{
			active = FALSE;					// �����ټ���
		}
		return 0;						// ������Ϣѭ��
	}
	case WM_SYSCOMMAND:						// ϵͳ�ж�����
	{
		switch (wParam)						// ���ϵͳ����
		{
		case SC_SCREENSAVE:				// ����Ҫ����?
		case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
			return 0;					// ��ֹ����
		}
		break;							// �˳�
	}
	case WM_CLOSE:							// �յ�Close��Ϣ?
	{
		PostQuitMessage(0);					// �����˳���Ϣ
		return 0;						// ����
	}
	case WM_KEYDOWN:						// �м�����ô?
	{
		keys[wParam] = TRUE;					// ����ǣ���ΪTRUE
		return 0;						// ����
	}
	case WM_KEYUP:							// �м��ſ�ô?
	{
		keys[wParam] = FALSE;					// ����ǣ���ΪFALSE
		return 0;						// ����
	}
	case WM_SIZE:							// ����OpenGL���ڴ�С
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));		// LoWord=Width,HiWord=Height
		return 0;						// ����
	}
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,				// ��ǰ����ʵ��
	HINSTANCE	hPrevInstance,				// ǰһ������ʵ��
	LPSTR		lpCmdLine,				// �����в���
	int		nCmdShow)				// ������ʾ״̬
{
	MSG	msg;								// Windowsx��Ϣ�ṹ

	BOOL	done = FALSE;							// �����˳�ѭ����Bool ����

	if (MessageBox(NULL, "FullScreen Modle��", "Set FullScreen", MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		fullscreen = FALSE;						// FALSEΪ����ģʽ
	}

	if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
	{
		return 0;							// ʧ���˳�
	}

	while (!done)								// ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))			// ����Ϣ�ڵȴ���?
		{
			if (msg.message == WM_QUIT)				// �յ��˳���Ϣ?
			{
				done = TRUE;					// �ǣ���done=TRUE
			}
			else							// ���ǣ���������Ϣ
			{
				TranslateMessage(&msg);				// ������Ϣ
				DispatchMessage(&msg);				// ������Ϣ
			}
		}
		else
		{
			if (active)						// ���򼤻��ô?
			{
				if (keys[VK_ESCAPE])				// ESC ������ô?
				{
					done = TRUE;				// ESC �����˳��ź�
				}
				else						// �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();				// ���Ƴ���
					SwapBuffers(hdc);			// �������� (˫����)
					if (example)
					{
						example->DoKeysAction();
					}
				}
			}

			if (keys[VK_F1])					// F1��������ô?
			{
				keys[VK_F1] = FALSE;				// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();					// ���ٵ�ǰ�Ĵ���
				fullscreen = !fullscreen;				// �л� ȫ�� / ���� ģʽ
				// �ؽ� OpenGL ����

#ifdef DEFAULT
				if (!CreateGLWindow("NeHe's OpenGL Framework", 640, 480, 16, fullscreen))
				{
					return 0;				
				}
#else
				if (example && !CreateGLWindow(example->GetGLWindowTitle(), 640, 480, 16, fullscreen))
				{
					return 0;				// �������δ�ܴ����������˳�
				}
#endif
			}
		}
	}

	KillGLWindow();								// ���ٴ���

	return (msg.wParam);							// �˳�����
}