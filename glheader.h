#ifndef GLHEADER_H
#define GLHEADER_H

#include <iostream>
#include <string>
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#include <GL/glew.h>
#else
#include <OpenGL/gl3.h>
#endif

void glError(const char *file, int line);

void glSetup();

///
/// Usage
/// [... some opengl calls]
/// glCheckError();
///
#define glCheckError() glError(__FILE__,__LINE__)

#endif // GLHEADER_H
