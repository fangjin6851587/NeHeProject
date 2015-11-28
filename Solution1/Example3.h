#ifndef EXAMPLE3_H
#define EXAMPLE3_H

#include <gl/glew.h>
#include "ExampleBase.h"

class Example3 : public ExampleBase
{
public:
	Example3();
	~Example3();

	virtual int DrawGLScene(GLvoid) override;

private:

	GLfloat rtri;
	GLfloat rquad;
};

#endif