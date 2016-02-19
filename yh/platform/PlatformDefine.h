#ifndef YH_PLATFORM_PLATFORM_DEFINE_H_
#define YH_PLATFORM_PLATFORM_DEFINE_H_

#include "./PlatformConfig.h"

#if YH_TARGET_PLATFORM == YH_PLATFORM_MAC
	#include "./mac/PlatformDefine-mac.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_IOS
	#include "./ios/PlatformDefine-ios.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID
	#include "./android/PlatformDefine-android.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
	#include "./win32/PlatformDefine-win32.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WINRT
	#include "./winrt/PlatformDefine-winrt.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_LINUX
	#include "./linux/PlatformDefine-linux.h"
#endif

#endif  // YH_PLATFORM_PLATFORM_DEFINE_H_

