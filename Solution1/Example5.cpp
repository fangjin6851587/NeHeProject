#include "Example5.h"

Example5::Example5()
{
}

Example5::~Example5()
{

}

void Example5::DoKeysAction()
{
	if (keys['L'] && !lp)
	{
		lp = TRUE;
		light = !light;
		if (!light)
		{
			glDisable(GL_LIGHTING);
		}
		else
		{
			glEnable(GL_LIGHTING);
		}
	}

	if (!keys['L'])
	{
		lp = FALSE;
	}

	if (keys['F'] && !fp)
	{
		fp = TRUE;
		filter += 1;
		if (filter > 2)
		{
			filter = 0;
		}
	}
	if (!keys['F'])
	{
		fp = FALSE;
	}

	if (keys['B'] && !bp)
	{
		bp = TRUE;
		blend = !blend;
		if (blend)
		{
			glEnable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			//glDepthMask(FALSE);
		}
		else
		{
			glDisable(GL_BLEND);
			glEnable(GL_DEPTH_TEST);
			//glDepthMask(TRUE);
		}
	}

	if (!keys['B'])
	{
		bp = FALSE;
	}

	if (keys[VK_PRIOR])
	{
		z -= 0.02f;
	}
	if (keys[VK_NEXT])
	{
		z += 0.02f;
	}

	if (keys[VK_UP])
	{
		xspeed -= 0.01f;
	}
	if (keys[VK_DOWN])
	{
		xspeed += 0.01f;
	}
	if (keys[VK_RIGHT])
	{
		yspeed += 0.01f;
	}
	if (keys[VK_LEFT])
	{
		yspeed -= 0.01f;
	}
}

int Example5::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, z);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glRotatef(zrot, 0.0f, 0.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture[filter]);

	glBegin(GL_QUADS);


	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);	// 纹理和四边形的左下

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);	// 纹理和四边形的右下

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);	// 纹理和四边形的右上

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);	// 纹理和四边形的左上

	// 后面

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);	// 纹理和四边形的右上

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);	// 纹理和四边形的左上

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下

	// 顶面

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);	// 纹理和四边形的左上

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);	// 纹理和四边形的左下

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);	// 纹理和四边形的右下

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);	// 纹理和四边形的右上

	// 底面

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的右上

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);	// 纹理和四边形的左上

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);	// 纹理和四边形的左下

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);	// 纹理和四边形的右下

	// 右面

	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);	// 纹理和四边形的右下

	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);	// 纹理和四边形的右上

	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);	// 纹理和四边形的左上

	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);	// 纹理和四边形的左下

	// 左面

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// 纹理和四边形的左下

	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);	// 纹理和四边形的右下

	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);	// 纹理和四边形的右上

	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);	// 纹理和四边形的左上

	glEnd();

	xrot += xspeed;
	yrot += yspeed;
	//zrot += 0.4f;

	return TRUE;
}

int Example5::InitGL(GLvoid)
{
	if (!LoadGLTextures())
	{
		return FALSE;
	}

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	return TRUE;
}

int Example5::LoadGLTextures()
{
	int status = FALSE;

	AUX_RGBImageRec* textureImage[1];
	memset(textureImage, 0, sizeof(void*) * 1);

	if (textureImage[0] = Util::LoadBMP("Data/Example5.bmp"))
	{
		status = TRUE;

		//create textures
		glGenTextures(3, &texture[0]);
		//bind texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		//generate texture, nearest filter
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, texture[1]);
		//generate texture, linear filter
		glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//create mipmapped
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, textureImage[0]->sizeX, textureImage[0]->sizeY, GL_RGBA, GL_UNSIGNED_BYTE, textureImage[0]->data);

		if (textureImage[0]->data)
		{
			free(textureImage[0]->data);
			free(textureImage[0]);
		}
	}

	return status;
}

const GLfloat Example5::LightAmbient[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

const GLfloat Example5::LightDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

const GLfloat Example5::LightPosition[4] = { 0.0f, 0.0f, 2.0f, 1.0f };
