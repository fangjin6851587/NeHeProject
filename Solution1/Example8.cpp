#include "Example8.h"
#include "Util.h"
#include "GlobalExampleDefine.h"


Example8::Example8()
{
	yrot = 0;
	xrot = 0;
}


Example8::~Example8()
{
}

void Example8::DoKeysAction()
{
	if (keys[VK_LEFT])				// 左键是否按下
	{
		yrot -= 0.2f;				// 如果是，向左旋转
	}

	if (keys[VK_RIGHT])				// 右键是否按下
	{
		yrot += 0.2f;				// 如果是向右旋转
	}

	if (keys[VK_UP])				// 上键是否按下
	{
		xrot -= 0.2f;				// 如果是向上旋转
	}

	if (keys[VK_DOWN])				// 下键是否按下
	{
		xrot += 0.2f;				// 如果是向下旋转
	}
}

int Example8::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	for (yloop = 1; yloop < 6; yloop++)
	{
		for (xloop = 0; xloop < yloop; xloop++)
		{
			glLoadIdentity();
			glTranslatef(1.4f + (float(xloop)*2.8f) - (float(yloop)*1.4f), ((6.0f - float(yloop))*2.4f) - 7.0f, -20.0f);
			glRotatef(45.0f - (2.0f*yloop) + xrot, 1.0f, 0.0f, 0.0f);
			glRotatef(45.0f + yrot, 0.0f, 1.0f, 0.0f);
			glColor3fv(boxcol[yloop - 1]);
			glCallList(box);
			glColor3fv(topcol[yloop - 1]);
			glCallList(top);
		}
	}

	return TRUE;
}

int Example8::InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return FALSE;
	}
	glEnable(GL_TEXTURE_2D);
	BuildLists();
	glEnable(GL_LIGHT0);					// 使用默认的0号灯
	glEnable(GL_LIGHTING);					// 使用灯光
	glEnable(GL_COLOR_MATERIAL);				// 使用颜色材质
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return ExampleBase::InitGL();
}

GLvoid Example8::BuildLists()
{
	box = glGenLists(2);
	glNewList(box, GL_COMPILE);

	glBegin(GL_QUADS);							// 开始绘制四边形

	// 底面

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	// 前面

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	// 后面

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	// 右面

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	// 左面

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();								// 四边形绘制结束

	glEndList();

	top = box + 1;
	glNewList(top, GL_COMPILE);

	glBegin(GL_QUADS);							// 开始绘制四边形

	// 上面

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glEnd();								// 结束绘制四边形

	glEndList();
}

GLfloat Example8::topcol[5][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.5f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f },
};

GLfloat Example8::boxcol[5][3] = {
		{ 1.0f, 0.0f, 0.0f },
		{ 1.0f, 0.5f, 0.0f },
		{ 1.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f },
};

int Example8::LoadGLTextures()
{
	return Util::LoadGLTextures("Data/Cube.bmp", texture, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
}
