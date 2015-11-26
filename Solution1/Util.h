#ifndef UTIL_H
#define  UTIL_H

#include <stdio.h>
#include <gl/GLAUX.H>

extern AUX_RGBImageRec *LoadBMP(const char* filename);
extern int LoadGLTextures(const char* filename, GLuint *texture);

#endif