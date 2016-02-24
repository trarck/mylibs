#ifndef YH_PLATFORM_PLATFORM_CONFIG_H_
#define YH_PLATFORM_PLATFORM_CONFIG_H_

//////////////////////////////////////////////////////////////////////////
// pre configure
//////////////////////////////////////////////////////////////////////////

// define supported target platform macro which YH uses.
#define YH_PLATFORM_UNKNOWN            0
#define YH_PLATFORM_IOS                1
#define YH_PLATFORM_ANDROID            2
#define YH_PLATFORM_WIN32              3
#define YH_PLATFORM_MARMALADE          4
#define YH_PLATFORM_LINUX              5
#define YH_PLATFORM_BADA               6
#define YH_PLATFORM_BLACKBERRY         7
#define YH_PLATFORM_MAC                8
#define YH_PLATFORM_NACL               9
#define YH_PLATFORM_EMSCRIPTEN        10
#define YH_PLATFORM_TIZEN             11
#define YH_PLATFORM_QT5               12
#define YH_PLATFORM_WINRT             13

// Determine target platform by compile environment macro.
#define YH_TARGET_PLATFORM             YH_PLATFORM_UNKNOWN

//check mac os
#if defined(__APPLE__) && defined(__MACH__)
	/* Apple OSX and iOS (Darwin). ------------------------------ */
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR == 1
	/* iOS in Xcode simulator */
	#undef  YH_TARGET_PLATFORM
	#define YH_TARGET_PLATFORM         YH_PLATFORM_IOS
#elif TARGET_OS_IPHONE == 1
	/* iOS on iPhone, iPad, etc. */
	#undef  YH_TARGET_PLATFORM
	#define YH_TARGET_PLATFORM         YH_PLATFORM_IOS
#elif TARGET_OS_MAC == 1
	/* OSX */
	#undef  YH_TARGET_PLATFORM
	#define YH_TARGET_PLATFORM         YH_PLATFORM_MAC
#endif
#endif

// // mac
// #if defined(YH_TARGET_OS_MAC)
// 	#undef  YH_TARGET_PLATFORM
// 	#define YH_TARGET_PLATFORM         YH_PLATFORM_MAC
// #endif
// 
// // iphone
// #if defined(YH_TARGET_OS_IPHONE)
//     #undef  YH_TARGET_PLATFORM
//     #define YH_TARGET_PLATFORM         YH_PLATFORM_IOS
// #endif

// android
#if defined(ANDROID)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM         YH_PLATFORM_ANDROID
#endif

// win32
#if defined(WIN32) && defined(_WINDOWS)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM         YH_PLATFORM_WIN32
#endif

// linux
#if defined(LINUX)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM         YH_PLATFORM_LINUX
#endif

// marmalade
#if defined(MARMALADE)
#undef  YH_TARGET_PLATFORM
#define YH_TARGET_PLATFORM         YH_PLATFORM_MARMALADE
#endif

// bada
#if defined(SHP)
#undef  YH_TARGET_PLATFORM
#define YH_TARGET_PLATFORM         YH_PLATFORM_BADA
#endif

// qnx
#if defined(__QNX__)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM     YH_PLATFORM_BLACKBERRY
#endif

// native client
#if defined(__native_client__)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM     YH_PLATFORM_NACL
#endif

// Emscripten
#if defined(EMSCRIPTEN)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM     YH_PLATFORM_EMSCRIPTEN
#endif

// tizen
#if defined(TIZEN)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM     YH_PLATFORM_TIZEN
#endif

// qt5
#if defined(YH_TARGET_QT5)
    #undef  YH_TARGET_PLATFORM
    #define YH_TARGET_PLATFORM     YH_PLATFORM_QT5
#endif

// WinRT (Windows 8.1 Store/Phone App)
#if defined(WINRT)
#undef  YH_TARGET_PLATFORM
#define YH_TARGET_PLATFORM          YH_PLATFORM_WINRT
#endif

//////////////////////////////////////////////////////////////////////////
// post configure
//////////////////////////////////////////////////////////////////////////

// check user set platform
#if ! YH_TARGET_PLATFORM
    #error  "Cannot recognize the target platform; are you targeting an unsupported platform?"
#endif 

#if (YH_TARGET_PLATFORM == YH_PLATFORM_WIN32)
#ifndef __MINGW32__
#pragma warning (disable:4127) 
#endif 
#endif  // YH_PLATFORM_WIN32

#endif  // YH_PLATFORM_PLATFORM_CONFIG_H_

