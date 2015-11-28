#ifndef EXAMPLE1_H
#define  EXAMPLE1_H

#include "ExampleBase.h"

class Example1 : public ExampleBase
{
public:
	Example1 ();
	~Example1 ();

	virtual int DrawGLScene(GLvoid) override;

private:

};
#endif