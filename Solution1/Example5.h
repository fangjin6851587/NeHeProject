#ifndef EXAMPLE5_H
#define EXAMPLE5_H

#include <gl/glew.h>
#include <gl/GLAUX.H>
#include <stdio.h>
#include "ExampleBase.h"
#include "Util.h"
#include "GlobalExampleDefine.h"

class Example5 : public ExampleBase
{
public:
	Example5();
	~Example5();

	virtual void DoKeysAction() override;

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

	virtual int LoadGLTextures() override;

private:

	static  const GLfloat LightAmbient[4];
	static const GLfloat LightDiffuse[4];
	static const GLfloat LightPosition[4];

	BOOL light = FALSE;
	BOOL lp = FALSE;
	BOOL fp = FALSE;
	BOOL blend = FALSE;
	BOOL bp = FALSE;

	GLfloat xrot = 0;
	GLfloat yrot = 0;
	GLfloat zrot = 0;

	GLfloat xspeed = 0;
	GLfloat yspeed = 0;
	GLfloat z = 0.1f;
	GLuint filter = 0;
	GLuint texture[3];
};

#endif