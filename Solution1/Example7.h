#pragma once
#include "ExampleBase.h"
class Example7 : public ExampleBase
{
public:
	Example7();
	~Example7();

	virtual void DoKeysAction() override;

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

	virtual int LoadGLTextures() override;

private:

	GLuint texture[1];
	float points[45][45][3];
	int wiggle_count = 0;
	GLfloat hold;
	GLfloat xrot;
	GLfloat yrot;
	GLfloat zrot;
};

