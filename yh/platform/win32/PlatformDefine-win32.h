#ifndef YH_PLATFORM_PLATFORMDEFINE_WIN32_H_
#define YH_PLATFORM_PLATFORMDEFINE_WIN32_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_WIN32

#ifdef __MINGW32__
#include <string.h>
#endif

#ifndef YH_DLL
	#if defined(YH_STATIC)
		#define YH_DLL
	#else
		#if defined(YH_USRDLL)
			#define YH_DLL     __declspec(dllexport)
		#else         /* use a DLL library */
			#define YH_DLL     __declspec(dllimport)
		#endif
	#endif
#endif //YH_DLL

#include <assert.h>

#if YH_DISABLE_ASSERT > 0
	#define YH_ASSERT(cond)
#else
	#define YH_ASSERT(cond)    assert(cond)
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

#endif //YH_TARGET_PLATFORM == YH_PLATFORM_WIN32

#endif /* YH_PLATFORM_PLATFORMDEFINE_WIN32_H_*/
