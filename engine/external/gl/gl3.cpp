#include "gl/gl3.h"

// gl
PFNGLGENBUFFERSPROC glGenBuffers = 0;
PFNGLBINDBUFFERPROC glBindBuffer = 0;
PFNGLBUFFERDATAPROC glBufferData = 0;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = 0;

// wgl
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = 0;

namespace {
    bool _gl3ExtensionsLoaded = false;
}
bool gl3LoadExtensions(void)
{
    // TODO: We only support openGL 3.2 or greater, support 2.1 - 3.2
    GLint major, minor;

    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if (major < 3 || (major == 3 && minor < 2))
    {
        return false;
    }

    if (!_gl3ExtensionsLoaded)
    {
        _gl3ExtensionsLoaded = true;

        // gl
        glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
        glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
        glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
        glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");

        // wgl
        wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    }

    return true;
}

bool gl3IsSupported(const char *extension)
{
    char *ext = (char *)glGetString(GL_EXTENSIONS);
    char *res = strstr(ext, extension);
    return res;
    //return strstr((char *)glGetString(GL_EXTENSIONS), extension) != 0;
}