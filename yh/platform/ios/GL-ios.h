#ifndef YH_PLATFORM_GL_IOS_H_
#define YH_PLATFORM_GL_IOS_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_IOS

#define glClearDepth                glClearDepthf
#define glDeleteVertexArrays        glDeleteVertexArraysOES
#define glGenVertexArrays           glGenVertexArraysOES
#define glBindVertexArray           glBindVertexArrayOES
#define glMapBuffer                 glMapBufferOES
#define glUnmapBuffer               glUnmapBufferOES

#define GL_DEPTH24_STENCIL8         GL_DEPTH24_STENCIL8_OES
#define GL_WRITE_ONLY               GL_WRITE_ONLY_OES

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#endif // YH_PLATFORM_IOS

#endif // YH_PLATFORM_GL_IOS_H_

