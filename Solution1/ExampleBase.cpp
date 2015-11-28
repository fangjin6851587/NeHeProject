#include "ExampleBase.h"

ExampleBase::ExampleBase()
{
}


ExampleBase::~ExampleBase()
{
}

int ExampleBase::DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	return TRUE;
}

void ExampleBase::DoKeysAction()
{

}

int ExampleBase::LoadGLTextures()
{
	return FALSE;
}

char* ExampleBase::GetGLWindowTitle()
{
	return "NeHe's OpenGL Framework";
}

int ExampleBase::InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return TRUE;
}
