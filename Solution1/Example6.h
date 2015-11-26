#ifndef EXAMPLE6_H
#define  EXAMPLE6_H

#include <stdio.h>
#include <gl/GLAUX.H>

static BOOL twinkle; //�Ƿ�����˸
static BOOL tp;

static const int num = 50;

typedef struct
{
	int r, g, b;
	GLfloat dis;
	GLfloat angle;
}starts;

static starts star[num];

static GLfloat zoom = -15.0f; //���Ǿ�۲��߾���
static GLfloat tilt = 90.0f; //���ǵ����
static GLfloat spin;		  //���ǵ���ת

static GLuint loop;
static GLuint texture[1];

extern int Example6_LoadGLTextures();
extern int Example6_InitGL(GLvoid);
extern int Example6_DrawGLScene(GLvoid);
extern void Example6_DoKeysAction(bool keys[]);

#endif // !EXAMPLE6_H

