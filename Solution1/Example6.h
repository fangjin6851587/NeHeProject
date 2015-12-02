#ifndef EXAMPLE6_H
#define  EXAMPLE6_H

#include "ExampleBase.h"
#include <stdio.h>
#include <gl/GLAUX.H>
#include "Util.h"
#include "GlobalExampleDefine.h"


class Example6 : public ExampleBase
{

public:
	Example6();
	~Example6();

	virtual void DoKeysAction() override;

	virtual int DrawGLScene(GLvoid) override;

	virtual int InitGL(GLvoid) override;

	virtual int LoadGLTextures() override;

	virtual char* GetGLWindowTitle() override;

private:

	typedef struct
	{
		int r, g, b;
		GLfloat dis;
		GLfloat angle;
	}starts;

	static const int num = 50;

	starts star[num];


	BOOL twinkle = FALSE; //�Ƿ�����˸
	BOOL tp = FALSE;

	GLfloat zoom = -15.0f; //���Ǿ�۲��߾���
	GLfloat tilt = 90.0f; //���ǵ����
	GLfloat spin = 0;		  //���ǵ���ת

	GLuint loop = 0;
	GLuint texture[1];
};

#endif // !EXAMPLE6_H

