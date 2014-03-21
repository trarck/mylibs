#ifndef YH_BASE_PLATFORM_DEFINE_H_
#define YH_BASE_PLATFORM_DEFINE_H_

#include "CCPlatformConfig.h"

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif //NULL

//unused param
#define YH_UNUSED_PARAM(unusedparam) (void)unusedparam

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
            TypeName(const TypeName&);\
            void operator=(const TypeName&)

//assert
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	#include "android/log.h"

	#define YH_NO_MESSAGE_PSEUDOASSERT(cond)                        \
	    if (!(cond)) {                                              \
	        __android_log_print(ANDROID_LOG_ERROR,                  \
	                            "yh assert",                 \
	                            "%s function:%s line:%d",           \
	                            __FILE__, __FUNCTION__, __LINE__);  \
	    }

	#define YH_MESSAGE_PSEUDOASSERT(cond, msg)                          \
	    if (!(cond)) {                                                  \
	        __android_log_print(ANDROID_LOG_ERROR,                      \
	                            "yh assert",                     \
	                            "file:%s function:%s line:%d, %s",      \
	                            __FILE__, __FUNCTION__, __LINE__, msg); \
	    }

	#define YH_ASSERT(cond) YH_NO_MESSAGE_PSEUDOASSERT(cond)

#else //other platforms
	#include <assert.h>
	#if YH_DISABLE_ASSERT > 0
	#define YH_ASSERT(cond)
	#else
	#define YH_ASSERT(cond) assert(cond)
	#endif //YH_DISABLE_ASSERT > 0

#endif //assert
	
//dll export
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	#ifdef __MINGW32__
	#include <string.h>
	#endif

	//#if defined(_USRDLL)
	//    #define YH_DLL     __declspec(dllexport)
	//#else         /* use a DLL library */
	//    #define YH_DLL     __declspec(dllimport)
	//#endif

	#define YH_DLL
#elif CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
	#if defined(_USRDLL)
	#define YH_DLL __attribute__ ((visibility ("default")))
	#else         /* use a DLL library */
	#define YH_DLL __attribute__ ((visibility ("default")))
	#endif
#else
	#define YH_DLL
#endif //dell export

#endif  // YH_BASE_PLATFORM_DEFINE_H_

