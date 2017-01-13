#ifndef YH_PLATFORM_GL_H_
#define YH_PLATFORM_GL_H_


#include "./PlatformConfig.h"

#if YH_TARGET_PLATFORM == YH_PLATFORM_MAC
#include "./mac/GL-mac.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_IOS
#include "./ios/GL-ios.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID
#include "./android/GL-android.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
#include "./win32/GL-win32.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WINRT
#include "./winrt/GL-winrt.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_LINUX
#include "./linux/GL-linux.h"
#endif


#endif /* YH_PLATFORM_GL_H_*/
