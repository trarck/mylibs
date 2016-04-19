#ifndef YH_PLATFORM_GL_WINRT_H_
#define YH_PLATFORM_GL_WINRT_H_

#define GL_BGRA						GL_BGRA_EXT
#define	glClearDepth				glClearDepthf
#define GL_WRITE_ONLY				GL_WRITE_ONLY_OES

#if YH_TARGET_PLATFORM == YH_PLATFORM_WINRT
#include "EGL/egl.h"
#include "EGL/eglext.h"
#include "EGL/eglplatform.h"
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "GLES3/gl3.h"

#define glMapBuffer                 glMapBufferOES

#else
#include "GL_Angle.h"
#endif



#endif // YH_PLATFORM_GL_WINRT_H_
