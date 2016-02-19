#ifndef YH_PLATFORM_YHSTDC_H_
#define YH_PLATFORM_YHSTDC_H_

#include "PlatformConfig.h"

#include "nullptr.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_MAC
#include "./mac/StdC-mac.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_IOS
#include "./ios/StdC-ios.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID
#include "./android/StdC-android.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
#include "./win32/StdC-win32.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_WINRT
#include "./winrt/StdC-winrt.h"
#elif YH_TARGET_PLATFORM == YH_PLATFORM_LINUX
#include "./linux/StdC-linux.h"
#endif

#endif  // YH_PLATFORM_YHSTDC_H_

