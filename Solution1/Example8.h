#pragma once
#include "ExampleBase.h"

class Example8 : public ExampleBase
{
public:
	Example8();
	~Example8();

	virtual void DoKeysAction() override;

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

private:
	GLuint box;
	GLuint top;
	GLuint xloop;
	GLuint yloop;
	GLuint texture[1];

	GLfloat xrot;
	GLfloat yrot;

	static GLfloat boxcol[5][3];
	static GLfloat topcol[5][3];
	GLvoid BuildLists();

	virtual int LoadGLTextures() override;

};

