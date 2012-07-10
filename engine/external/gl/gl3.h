#ifndef __gl3_h_
#define __gl3_h_

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "gl/glext.h"
#include "gl/wglext.h"

bool gl3LoadExtensions(void);
bool gl3IsSupported(const char *extension);

// gl
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLBINDBUFFERPROC glBindBuffer;
extern PFNGLBUFFERDATAPROC glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;

// wgl
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;

#endif // __gl3_h_
