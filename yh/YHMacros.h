#ifndef YH_YHMACROS_H_
#define YH_YHMACROS_H_

#include "NSMacros.h"
#include "platform/PlatformConfig.h"
#include "platform/PlatformDefine.h"
#include "platform/Log.h"

#ifndef YHASSERT
#if defined(YH_DEBUG)
#define YHASSERT(cond, msg) do {                              \
      if (!(cond)) {                                          \
          yh::log("Assert failed: %s", msg);             	  \
        YH_ASSERT(cond);                                      \
      } 													  \
    } while (0)
#else
#define YHASSERT(cond, msg) 
#endif // YH_DEBUG>0
#endif  // YHASSERT
		
#endif //YH_YHMACROS_H_