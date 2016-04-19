#ifndef YH_PLATFORM_GL_ANGLE_H_
#define YH_PLATFORM_GL_ANGLE_H_

// disable unimplemented function declarations in Angle
#define GL_OES_mapbuffer 1
#define GL_OES_vertex_array_object 1

#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "winrtangle.h"
#include "esUtil.h"
#include "../PlatformDefine.h"

#define GL_WRITE_ONLY_OES                                       0x88B9
#define GL_BUFFER_ACCESS_OES                                    0x88BB
#define GL_BUFFER_MAPPED_OES                                    0x88BC
#define GL_BUFFER_MAP_POINTER_OES                               0x88BD



inline void glGenVertexArrays(GLsizei n, GLuint *arrays)
{
    YH_ASSERT(false, "AngleProject does not implement glGenVertexArraysOES");
}

inline void glBindVertexArray(GLuint array)
{
    YH_ASSERT(false, "AngleProject does not implement glBindVertexArrayOES");
}

inline void glDeleteVertexArrays(GLsizei n, const GLuint *arrays)
{
    YH_ASSERT(false, "AngleProject does not implement glDeleteVertexArraysOES");
}

inline void* glMapBuffer(GLenum target, GLenum access)
{
   YH_ASSERT(false, "AngleProject does not implement glMapBufferOES"); 
   return NULL;
}

inline GLboolean glUnmapBuffer(GLenum targets)
{
   YH_ASSERT(false, "AngleProject does not implement glUnmapBufferOES"); 
   return false;
}

#define GL_DEPTH24_STENCIL8			GL_DEPTH24_STENCIL8_OES

#endif // YH_PLATFORM_GL_ANGLE_H_
