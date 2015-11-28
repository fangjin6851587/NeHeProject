#ifndef EXAMPLE4_H
#define EXAMPLE4_H

#include <gl/glew.h>
#include "ExampleBase.h"

class Example4 : public ExampleBase
{
public:
	Example4();
	~Example4();

	virtual int DrawGLScene(GLvoid) override;

private:
	GLfloat rtri;
	GLfloat rquad;
};

#endif