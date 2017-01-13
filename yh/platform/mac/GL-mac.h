#ifndef YH_PLATFORM_GL_MAC_H_
#define YH_PLATFORM_GL_MAC_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_MAC

#import <OpenGL/gl.h>
#import <OpenGL/glu.h>
#import <OpenGL/glext.h>

#define YH_GL_DEPTH24_STENCIL8      -1


#define glDeleteVertexArrays            glDeleteVertexArraysAPPLE
#define glGenVertexArrays               glGenVertexArraysAPPLE
#define glBindVertexArray               glBindVertexArrayAPPLE
#define glClearDepthf                   glClearDepth
#define glDepthRangef                   glDepthRange
#define glReleaseShaderCompiler(xxx)

#endif //s YH_TARGET_PLATFORM == YH_PLATFORM_MAC

#endif // YH_PLATFORM_GL_MAC_H_


