#ifndef EXAMPLE2_H
#define EXAMPLE2_H
#include <gl/glew.h>
#include "ExampleBase.h"

class Example2:public ExampleBase
{
public:
	Example2();
	~Example2();

	virtual int DrawGLScene(GLvoid) override;

private:

};

#endif