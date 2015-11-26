#ifndef EXAMPLE6_H
#define  EXAMPLE6_H

#include <stdio.h>
#include <gl/GLAUX.H>

static BOOL twinkle; //ÊÇ·ñ¿ªÆôÉÁË¸
static BOOL tp;

static const int num = 50;

typedef struct
{
	int r, g, b;
	GLfloat dis;
	GLfloat angle;
}starts;

static starts star[num];

static GLfloat zoom = -15.0f; //ÐÇÐÇ¾à¹Û²ìÕß¾àÀë
static GLfloat tilt = 90.0f; //ÐÇÐÇµÄÇã½Ç
static GLfloat spin;		  //ÐÇÐÇµÄ×Ô×ª

static GLuint loop;
static GLuint texture[1];

extern int Example6_LoadGLTextures();
extern int Example6_InitGL(GLvoid);
extern int Example6_DrawGLScene(GLvoid);
extern void Example6_DoKeysAction(bool keys[]);

#endif // !EXAMPLE6_H

