#ifndef YH_BASE_YHMACROS_H_
#define YH_BASE_YHMACROS_H_

#include "../platform/PlatformConfig.h"
#include "../platform/PlatformDefine.h"

#ifdef __cplusplus

#define NS_YH_BEGIN                     namespace yh {
#define NS_YH_END                       }
#define USING_NS_YH                     using namespace yh

#else

#define NS_YH_BEGIN                     
#define NS_YH_END                       
#define USING_NS_YH

#endif

#ifndef YHASSERT
#if YH_DEBUG > 0
#define YHASSERT(cond, msg) do {                              \
      if (!(cond)) {                                          \
          printf("Assert failed: %s", msg);             	  \
        YH_ASSERT(cond);                                      \
      } 													  \
    } while (0)
#else
#define YHASSERT(cond, msg)
#endif // YH_DEBUG>0
#endif  // YHASSERT
		
#endif //YH_BASE_YHMACROS_H_