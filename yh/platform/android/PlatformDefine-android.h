#ifndef YH_PLATFORM_PLATFORM_DEFINE_ANDROID_H_
#define YH_PLATFORM_PLATFORM_DEFINE_ANDROID_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID

#include "android/log.h"

#ifndef YH_DLL
#define YH_DLL
#endif

#define YH_NO_MESSAGE_PSEUDOASSERT(cond)                        \
    if (!(cond)) {                                              \
        __android_log_print(ANDROID_LOG_ERROR,                  \
                            "cocos2d-x assert",                 \
                            "%s function:%s line:%d",           \
                            __FILE__, __FUNCTION__, __LINE__);  \
    }

#define YH_MESSAGE_PSEUDOASSERT(cond, msg)                          \
    if (!(cond)) {                                                  \
        __android_log_print(ANDROID_LOG_ERROR,                      \
                            "cocos2d-x assert",                     \
                            "file:%s function:%s line:%d, %s",      \
                            __FILE__, __FUNCTION__, __LINE__, msg); \
    }

#define YH_ASSERT(cond) YH_NO_MESSAGE_PSEUDOASSERT(cond)

#define YH_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID

#endif /* YH_PLATFORM_PLATFORM_DEFINE_ANDROID_H_*/
