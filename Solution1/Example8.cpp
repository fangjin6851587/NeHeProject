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
	if (keys[VK_LEFT])				// ����Ƿ���
	{
		yrot -= 0.2f;				// ����ǣ�������ת
	}

	if (keys[VK_RIGHT])				// �Ҽ��Ƿ���
	{
		yrot += 0.2f;				// �����������ת
	}

	if (keys[VK_UP])				// �ϼ��Ƿ���
	{
		xrot -= 0.2f;				// �����������ת
	}

	if (keys[VK_DOWN])				// �¼��Ƿ���
	{
		xrot += 0.2f;				// �����������ת
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
	glEnable(GL_LIGHT0);					// ʹ��Ĭ�ϵ�0�ŵ�
	glEnable(GL_LIGHTING);					// ʹ�õƹ�
	glEnable(GL_COLOR_MATERIAL);				// ʹ����ɫ����
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	return ExampleBase::InitGL();
}

GLvoid Example8::BuildLists()
{
	box = glGenLists(2);
	glNewList(box, GL_COMPILE);

	glBegin(GL_QUADS);							// ��ʼ�����ı���

	// ����

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	// ǰ��

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	// ����

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	// ����

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	// ����

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glEnd();								// �ı��λ��ƽ���

	glEndList();

	top = box + 1;
	glNewList(top, GL_COMPILE);

	glBegin(GL_QUADS);							// ��ʼ�����ı���

	// ����

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	glEnd();								// ���������ı���

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
