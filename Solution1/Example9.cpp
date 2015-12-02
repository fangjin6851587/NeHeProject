#include "Example9.h"
#include "GlobalExampleDefine.h"
#include <stdio.h>
#include <math.h>


Example9::Example9()
	:base(0), cnt1(0), cnt2(0)
{
}


Example9::~Example9()
{
}

GLvoid Example9::BuildFont(GLvoid)
{
	HFONT font;
	HFONT oldfont;

	base = glGenLists(96);
	font = CreateFont(
		-24,		// ����߶�
		0,		// ������
		0,		// �������ת�Ƕ� Angle Of Escapement
		0,		// ������ߵ���ת�Ƕ�Orientation Angle
		FW_BOLD, // ���������
		FALSE,  // �Ƿ�ʹ��б��
		FALSE,				// �Ƿ�ʹ���»���
		FALSE,				// �Ƿ�ʹ��ɾ����
		ANSI_CHARSET,			// �����ַ���
		OUT_TT_PRECIS,			// �������
		CLIP_DEFAULT_PRECIS,		// �ü�����
		ANTIALIASED_QUALITY,		// �������
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Courier New"			// ��������
		);

	oldfont = (HFONT)SelectObject(hdc, font);
	wglUseFontBitmaps(hdc, 32, 96, base);
	SelectObject(hdc, oldfont);
	DeleteObject(font);
}

GLvoid Example9::KillFont(GLvoid)
{
	glDeleteLists(base, 96);
}

GLvoid Example9::glPrint(const char *fmt, ...)
{
	char text[256];
	va_list ap;
	if (fmt == NULL)
		return;

	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base - 32);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

int Example9::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -1.0f);
	glColor3f(1.0f*float(cos(cnt1)), 1.0f*float(sin(cnt2)), 1.0f - 0.5f*float(cos(cnt1 + cnt2)));
	glRasterPos2f(-0.45f + 0.05f*float(cos(cnt1)), 0.35f*float(sin(cnt2)));

	glPrint("Active OpenGL Text With NeHe - %7.2f", cnt1);		// ������ֵ���Ļ

	cnt1 += 0.051f;						// ���Ӽ�����ֵ
	cnt2 += 0.005f;						// ���Ӽ�����ֵ

	return TRUE;						// ��������
}

int Example9::InitGL(GLvoid)
{
	BuildFont();
	return ExampleBase::InitGL();
}

void Example9::KillWindow()
{
	KillFont();
}
