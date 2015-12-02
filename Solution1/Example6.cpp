#include "Example6.h"


Example6::Example6()
{
}

Example6::~Example6()
{

}

void Example6::DoKeysAction()
{
	if (keys['T'] && !tp)
	{
		tp = TRUE;
		twinkle = !twinkle;
	}
	if (!keys['T'])
	{
		tp = FALSE;
	}

	if (keys[VK_UP])				// �Ϸ����������ô��
	{
		tilt -= 0.5f;				// ��Ļ������б
	}

	if (keys[VK_DOWN])				// �·����������ô��
	{
		tilt += 0.5f;				// ��Ļ������б
	}

	if (keys[VK_PRIOR])				// ���Ϸ�ҳ��������ô
	{
		zoom -= 0.2f;				// ��С
	}

	if (keys[VK_NEXT])				// ���·�ҳ��������ô��
	{
		zoom += 0.2f;				// �Ŵ�
	}
}

int Example6::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	for (loop = 0; loop < num; loop++)
	{
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, zoom);
		glRotatef(tilt, 1.0f, 0.0f, 0.0f);

		glRotatef(star[loop].angle, 0.0f, 1.0f, 0.0f);
		glTranslatef(star[loop].dis, 0.0f, 0.0f);

		glRotatef(-star[loop].angle, 0.0f, 1.0f, 0.0f);
		glRotatef(-tilt, 1.0f, 0.0f, 0.0f);

		if (twinkle)
		{
			unsigned int index = num - loop - 1;
			glColor4ub(star[index].r, star[index].g, star[index].b, 255);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
			glEnd();
		}

		glRotatef(spin, 0.0f, 0.0f, 1.0f);

		// ʹ��byte����ֵָ��һ����ɫ
		glColor4ub(star[loop].r, star[loop].g, star[loop].b, 255);
		glBegin(GL_QUADS);				// ��ʼ��������ӳ������ı���
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();					// �ı��λ��ƽ���


		spin += 0.01f;
		star[loop].angle += (float)(loop) / num;
		star[loop].dis -= 0.01f;

		if (star[loop].dis < 0.0f)
		{
			star[loop].dis += 5.0f;
			star[loop].r = rand() % 256;
			star[loop].g = rand() % 256;
			star[loop].b = rand() % 256;
		}
	}

	return TRUE;
}

int Example6::InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return FALSE;
	}

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);

	for (loop = 0; loop < num; loop++)
	{
		star[loop].angle = 0.0f;
		star[loop].dis = ((float)loop / num) * 5.0f;
		star[loop].r = rand() % 256;
		star[loop].g = rand() % 256;
		star[loop].b = rand() % 256;
	}

	return TRUE;
}

int Example6::LoadGLTextures()
{
	return Util::LoadGLTextures("Data/Star.bmp", texture);
}

char* Example6::GetGLWindowTitle()
{
	return "Example6";
}
