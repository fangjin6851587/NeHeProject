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

	if (keys[VK_UP])				// 上方向键按下了么？
	{
		tilt -= 0.5f;				// 屏幕向上倾斜
	}

	if (keys[VK_DOWN])				// 下方向键按下了么？
	{
		tilt += 0.5f;				// 屏幕向下倾斜
	}

	if (keys[VK_PRIOR])				// 向上翻页键按下了么
	{
		zoom -= 0.2f;				// 缩小
	}

	if (keys[VK_NEXT])				// 向下翻页键按下了么？
	{
		zoom += 0.2f;				// 放大
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

		// 使用byte型数值指定一个颜色
		glColor4ub(star[loop].r, star[loop].g, star[loop].b, 255);
		glBegin(GL_QUADS);				// 开始绘制纹理映射过的四边形
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
		glEnd();					// 四边形绘制结束


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
