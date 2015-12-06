#include "Example10.h"
#include "GlobalExampleDefine.h"
#include <stdio.h>
#include <math.h>
#include "Util.h"

Example10::Example10()
{
	base = 0;
	rot = 0;
}


Example10::~Example10()
{
}

int Example10::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();					// ���õ�ǰ��ģ�͹۲����
	glTranslatef(1.1f*float(cos(rot / 16.0f)), 0.8f*float(sin(rot / 20.0f)), -3.0f);
	glRotatef(rot, 1.0f, 0.0f, 0.0f);			// ��X����ת
	glRotatef(rot*1.5f, 0.0f, 1.0f, 0.0f);			// ��Y����ת
	glRotatef(rot*1.4f, 0.0f, 0.0f, 1.0f);			// ��Z����ת
	glTranslatef(-0.35f, -0.35f, 0.1f);				// �ƶ���������ʾ��λ��
	//glColor3f(1.0f*float(cos(rot / 20.0f)), 1.0f*float(sin(rot / 25.0f)), 1.0f - 0.5f*float(cos(rot / 17.0f)));
	glPrint("Nehe - %3.2f", rot / 50);				// ������ֵ���Ļ
	rot += 0.1f;						// ������ת����
	return TRUE;						// �ɹ�����

}

int Example10::InitGL(GLvoid)
{
	if (!LoadGLTextures())					// ��������
	{
		return FALSE;					// ʧ���򷵻�
	}

	BuildFont();						// ����������ʾ�б�

	glShadeModel(GL_SMOOTH);					// ������Ӱƽ��

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// ��ɫ����

	glClearDepth(1.0f);					// ������Ȼ���

	glEnable(GL_DEPTH_TEST);					// ������Ȳ���

	glDepthFunc(GL_LEQUAL);					// ������Ȳ��Ե�����

	glEnable(GL_LIGHT0);					// ʹ�õ�0�ŵ�

	glEnable(GL_LIGHTING);					// ʹ�ù���

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// ����ϵͳ��͸�ӽ�������

	glEnable(GL_TEXTURE_2D);					// ʹ�ö�ά����

	glBindTexture(GL_TEXTURE_2D, texture[0]);			// ѡ��ʹ�õ�����

	return TRUE;						// ��ʼ���ɹ�
}

void Example10::KillWindow()
{
	KillFont();
}

GLvoid Example10::glPrint(const char *fmt, ...)
{
	char text[256];
	va_list ap;
	float length = 0;
	if (fmt == NULL)
		return;

	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	for (unsigned int loop = 0; loop < strlen(text); loop++)
	{
		length += gmf[text[loop]].gmfCellIncX;
	}

	glTranslatef(-length*0.5f, 0.0f, 0.0f);

	glPushAttrib(GL_LIST_BIT);
	glListBase(base);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
	glPopAttrib();
}

GLvoid Example10::BuildFont(GLvoid)
{
	HFONT font;
	HFONT oldfont;

	base = glGenLists(256);
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
	wglUseFontOutlines(hdc, 0, 256, base, 0.0f, 0.2f, WGL_FONT_POLYGONS, gmf);
	SelectObject(hdc, oldfont);
	DeleteObject(font);
}

GLvoid Example10::KillFont(GLvoid)
{
	glDeleteLists(base, 256);
}

int Example10::LoadGLTextures()
{
	int code = Util::LoadGLTextures("Data/Lights.bmp", texture, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	// ��������ӳ��ģʽ
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);				// ʹ���Զ���������
	glEnable(GL_TEXTURE_GEN_T);
	return code;
}
