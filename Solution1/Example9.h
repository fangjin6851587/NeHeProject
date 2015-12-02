#pragma once
#include "ExampleBase.h"
class Example9 : public ExampleBase
{
public:
	Example9();
	~Example9();

private:
	GLuint base;

	GLfloat cnt1;
	GLfloat cnt2;

	GLvoid BuildFont(GLvoid);
	GLvoid KillFont(GLvoid);
	GLvoid glPrint(const char *fmt, ...);

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

	virtual void KillWindow() override;

};

