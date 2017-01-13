#ifndef YH_PLATFORM_PLATFORM_DEFINE_MAC_H_
#define YH_PLATFORM_PLATFORM_DEFINE_MAC_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_MAC

#include <assert.h>

#ifndef YH_DLL
	#ifdef _USRDLL
	#define YH_DLL __attribute__((visibility("default"))) 
	#else
	#define YH_DLL
	#endif //_USRDLL
#endif //YH_DLL

#if YH_DISABLE_ASSERT > 0
#define YH_ASSERT(cond)
#else
#define YH_ASSERT(cond) assert(cond)
#endif

#define YH_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_MAC

#endif /* YH_PLATFORM_PLATFORM_DEFINE_MAC_H_*/
