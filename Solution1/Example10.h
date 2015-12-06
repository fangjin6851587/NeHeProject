#pragma once
#include "ExampleBase.h"
class Example10 : public ExampleBase
{
public:
	Example10();
	~Example10();

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

	virtual void KillWindow() override;

private:

	GLuint base;
	GLfloat rot;
	GLYPHMETRICSFLOAT gmf[256];
	GLuint texture[1];

	GLvoid BuildFont(GLvoid);
	GLvoid KillFont(GLvoid);
	GLvoid glPrint(const char *fmt, ...);

	virtual int LoadGLTextures() override;

};

