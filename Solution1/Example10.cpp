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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕及深度缓存
	glLoadIdentity();					// 重置当前的模型观察矩阵
	glTranslatef(1.1f*float(cos(rot / 16.0f)), 0.8f*float(sin(rot / 20.0f)), -3.0f);
	glRotatef(rot, 1.0f, 0.0f, 0.0f);			// 沿X轴旋转
	glRotatef(rot*1.5f, 0.0f, 1.0f, 0.0f);			// 沿Y轴旋转
	glRotatef(rot*1.4f, 0.0f, 0.0f, 1.0f);			// 沿Z轴旋转
	glTranslatef(-0.35f, -0.35f, 0.1f);				// 移动到可以显示的位置
	//glColor3f(1.0f*float(cos(rot / 20.0f)), 1.0f*float(sin(rot / 25.0f)), 1.0f - 0.5f*float(cos(rot / 17.0f)));
	glPrint("Nehe - %3.2f", rot / 50);				// 输出文字到屏幕
	rot += 0.1f;						// 增加旋转变量
	return TRUE;						// 成功返回

}

int Example10::InitGL(GLvoid)
{
	if (!LoadGLTextures())					// 载入纹理
	{
		return FALSE;					// 失败则返回
	}

	BuildFont();						// 创建字体显示列表

	glShadeModel(GL_SMOOTH);					// 启用阴影平滑

	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			// 黑色背景

	glClearDepth(1.0f);					// 设置深度缓存

	glEnable(GL_DEPTH_TEST);					// 启用深度测试

	glDepthFunc(GL_LEQUAL);					// 所作深度测试的类型

	glEnable(GL_LIGHT0);					// 使用第0号灯

	glEnable(GL_LIGHTING);					// 使用光照

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);		// 告诉系统对透视进行修正

	glEnable(GL_TEXTURE_2D);					// 使用二维纹理

	glBindTexture(GL_TEXTURE_2D, texture[0]);			// 选择使用的纹理

	return TRUE;						// 初始化成功
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
		-24,		// 字体高度
		0,		// 字体宽度
		0,		// 字体的旋转角度 Angle Of Escapement
		0,		// 字体底线的旋转角度Orientation Angle
		FW_BOLD, // 字体的重量
		FALSE,  // 是否使用斜体
		FALSE,				// 是否使用下划线
		FALSE,				// 是否使用删除线
		ANSI_CHARSET,			// 设置字符集
		OUT_TT_PRECIS,			// 输出精度
		CLIP_DEFAULT_PRECIS,		// 裁剪精度
		ANTIALIASED_QUALITY,		// 输出质量
		FF_DONTCARE | DEFAULT_PITCH,		// Family And Pitch
		"Courier New"			// 字体名称
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
	// 设置纹理映射模式
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glEnable(GL_TEXTURE_GEN_S);				// 使用自动生成纹理
	glEnable(GL_TEXTURE_GEN_T);
	return code;
}
