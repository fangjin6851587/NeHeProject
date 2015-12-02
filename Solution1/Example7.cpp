#include "Example7.h"
#include "Util.h"
#include <math.h>


Example7::Example7()
	:xrot(0), 
	yrot(0), 
	zrot(0)
{
	for (int x = 0; x < 45; x++)
	{
		for (int y = 0; y < 45; y++)
		{
			points[x][y][0] = float((x / 5.0f) - 4.5f);
			points[x][y][1] = float((y / 5.0f) - 4.5f);
			points[x][y][2] = float(sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.14159265358979323846 * 2.0f));
		}
	}
}

Example7::~Example7()
{
}


void Example7::DoKeysAction()
{
}

int Example7::DrawGLScene(GLvoid)
{
	int x, y;
	float float_x, float_y, float_xb, float_yb;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -12.0f);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);				// 绕 X 轴旋转
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);				// 绕 Y 轴旋转
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);				// 绕 Z 轴旋转

	glBindTexture(GL_TEXTURE_2D, texture[0]);		// 选择纹理
	glBegin(GL_QUADS);
	for (x = 0; x < 44; x++)
	{
		for (y = 0; y < 44; y++)
		{
			float_x = float(x) / 44.0f;		// 生成X浮点值
			float_y = float(y) / 44.0f;		// 生成Y浮点值
			float_xb = float(x + 1) / 44.0f;		// X浮点值+0.0227f
			float_yb = float(y + 1) / 44.0f;		// Y浮点值+0.0227f

			glTexCoord2f(float_x, float_y);	// 第一个纹理坐标 (左下角)
			glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

			glTexCoord2f(float_x, float_yb);	// 第二个纹理坐标 (左上角)
			glVertex3f(points[x][y + 1][0], points[x][y + 1][1], points[x][y + 1][2]);

			glTexCoord2f(float_xb, float_yb);	// 第三个纹理坐标 (右上角)
			glVertex3f(points[x + 1][y + 1][0], points[x + 1][y + 1][1], points[x + 1][y + 1][2]);

			glTexCoord2f(float_xb, float_y);	// 第四个纹理坐标 (右下角)
			glVertex3f(points[x + 1][y][0], points[x + 1][y][1], points[x + 1][y][2]);
		}
	}
	glEnd();

	if (wiggle_count == 2)
	{
		for (y = 0; y < 45; y++)
		{
			hold = points[0][y][2];
			for (x = 0; x < 44; x++)
			{
				points[x][y][2] = points[x + 1][y][2];
			}
			points[44][y][2] = hold;
		}
		wiggle_count = 0;
	}
	wiggle_count++;

	xrot += 0.3f;
	yrot += 0.2f;
	zrot += 0.4f;

	return TRUE;
}

int Example7::InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return FALSE;
	}

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glPolygonMode(GL_BACK, GL_FILL);			// 后表面完全填充
	glPolygonMode(GL_FRONT, GL_LINE);			// 前表面使用线条绘制

	return TRUE;
}

int Example7::LoadGLTextures()
{
	return Util::LoadGLTextures("Data/Tim.bmp", texture);
}
