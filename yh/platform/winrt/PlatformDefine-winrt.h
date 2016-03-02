#ifndef YH_PLATFORM_PLATFORM_DEFINE_WINRT_H_
#define YH_PLATFORM_PLATFORM_DEFINE_WINRT_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_WINRT

#ifndef YH_DLL
	#if defined(YH_STATIC)
		#define YH_DLL
	#else
		#if defined(YH_USRDLL)
			#define YH_DLL     __declspec(dllexport)
		#else         /* use a DLL library */
			#define YH_DLL		__declspec(dllimport)
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

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_WINRT

#endif /* YH_PLATFORM_PLATFORM_DEFINE_WINRT_H_*/
