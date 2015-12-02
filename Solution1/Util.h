#ifndef UTIL_H
#define  UTIL_H

#include <stdio.h>
#include <gl/GLAUX.H>

class Util
{
public:
	Util();
	~Util();

	static AUX_RGBImageRec *LoadBMP(const char* filename);
	static int LoadGLTextures(const char* filename, GLuint *texture, GLint minfilter = GL_LINEAR, GLint magfilter = GL_LINEAR);
};

#endif