#pragma once
#include <gl/GLAUX.H>

class ExampleBase
{
private:


protected:
	 virtual int LoadGLTextures();


public:
	ExampleBase();
	~ExampleBase();

	virtual int InitGL(GLvoid);
	virtual int DrawGLScene(GLvoid);
	virtual void DoKeysAction();
	virtual char* GetGLWindowTitle();
};

