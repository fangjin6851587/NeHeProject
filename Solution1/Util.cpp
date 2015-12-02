#include "Util.h"

Util::Util()
{

}

Util::~Util()
{

}

AUX_RGBImageRec * Util::LoadBMP(const char* filename)
{
	FILE* file = NULL;

	if (!filename)
	{
		return NULL;
	}

	fopen_s(&file, filename, "r");
	if (file)
	{
		fclose(file);
		return auxDIBImageLoad(filename);
	}

	return NULL;
}

int Util::LoadGLTextures(const char* filename, GLuint *texture, GLint minfilter /*= GL_LINEAR*/, GLint magfilter /*= GL_LINEAR*/)
{
	int status = FALSE;

	if (NULL != texture)
	{
		AUX_RGBImageRec *textImage[1];
		memset(textImage, 0, sizeof(void*));

		if (textImage[0] = LoadBMP(filename))
		{
			status = TRUE;

			glGenTextures(1, &texture[0]);
			glBindTexture(GL_TEXTURE_2D, texture[0]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minfilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magfilter);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textImage[0]->sizeX, textImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, textImage[0]->data);
		}

		if (textImage[0])
		{
			if (textImage[0]->data)
			{
				free(textImage[0]->data);
			}
			free(textImage[0]);
		}
	}

	return status;
}
