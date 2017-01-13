#ifndef YH_PLATFORM_PLATFORM_DEFINE_IOS_H_
#define YH_PLATFORM_PLATFORM_DEFINE_IOS_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_IOS

#include <assert.h>

#ifndef YH_DLL
#define YH_DLL 
#endif

#define YH_ASSERT(cond) assert(cond)


#define YH_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif


#endif // YH_TARGET_PLATFORM == YH_PLATFORM_IOS

#endif /* YH_PLATFORM_PLATFORM_DEFINE_IOS_H_*/
