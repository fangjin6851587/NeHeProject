#ifndef EXAMPLE5_H
#define EXAMPLE5_H

#include <gl/glew.h>
#include <gl/GLAUX.H>
#include <stdio.h>

static BOOL light;
static BOOL lp;
static BOOL fp;

static GLfloat xrot;
static GLfloat yrot;
static GLfloat zrot;

static GLfloat xspeed;
static GLfloat yspeed;

static GLfloat z = -0.5f;
static GLfloat LightAmbient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
static GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
static GLfloat LightPosition[] = { 0.0f, 0.0f, 2.0f, 1.0f };

static GLuint filter;

static GLuint texture[3];

extern AUX_RGBImageRec* Example5_LoadBMP(char* filename);
extern int Example5_LoadGLTextures();
extern int Example5_InitGL(GLvoid);
extern int Example5_DrawGLScene(GLvoid);
extern void Example5_DoKeysAction(int index, BOOL press);

#endif