#ifndef YH_PLATFORM_PLATFORM_DEFINE_H_
#define YH_PLATFORM_PLATFORM_DEFINE_H_

#include "PlatformConfig.h"

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

//disable copy and assign
#define YH_DISALLOW_COPY_AND_ASSIGN(TypeName) \
            TypeName(const TypeName&);\
            void operator=(const TypeName&)

//disable copy and assign
#if defined(__GNUC__) && ((__GNUC__ >= 5) || ((__GNUG__ == 4) && (__GNUC_MINOR__ >= 4))) \
|| (defined(__clang__) && (__clang_major__ >= 3))
#define YH_DISABLE_COPY(Class) \
private: \
Class(const Class &) = delete; \
Class &operator =(const Class &) = delete;
#else
#define YH_DISABLE_COPY(Class) \
private: \
Class(const Class &); \
Class &operator =(const Class &);
#endif

//assert
#if YH_DISABLE_ASSERT > 0
	#define YH_ASSERT(cond)
#else //YH_DISABLE_ASSERT > 0
#if YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID
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
	#define YH_ASSERT(cond) assert(cond)
#endif //assert
#endif //YH_DISABLE_ASSERT > 0

//dll export
#if YH_TARGET_PLATFORM == YH_PLATFORM_WIN32
	#if defined(_USRDLL)
	    #define YH_DLL     __declspec(dllexport)
	#else         /* use a DLL library */
	    #define YH_DLL     __declspec(dllimport)
	#endif

	#define YH_DLL
#elif YH_TARGET_PLATFORM == YH_PLATFORM_LINUX
	#if defined(_USRDLL)
	#define YH_DLL __attribute__ ((visibility ("default")))
	#else         /* use a DLL library */
	#define YH_DLL __attribute__ ((visibility ("default")))
	#endif
#else
	#define YH_DLL
#endif //dell export

#endif  // YH_PLATFORM_PLATFORM_DEFINE_H_

