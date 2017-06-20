#ifndef YH_YHMACROS_H_
#define YH_YHMACROS_H_

#include "NSMacros.h"
#include "platform/PlatformConfig.h"
#include "platform/PlatformDefine.h"
#include "platform/Log.h"
#include "platform/YHStdC.h"

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

#define YH_SAFE_DELETE(p)            do { if(p) { delete (p); (p) = 0; } } while(0)
#define YH_SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = 0; } } while(0)
#define YH_SAFE_FREE(p)                do { if(p) { free(p); (p) = 0; } } while(0)
#define YH_SAFE_RELEASE(p)            do { if(p) { (p)->release(); } } while(0)
#define YH_SAFE_RELEASE_NULL(p)        do { if(p) { (p)->release(); (p) = 0; } } while(0)
#define YH_SAFE_RETAIN(p)            do { if(p) { (p)->retain(); } } while(0)

//macro to string
#define YH_TO_STRING(s) YH_TO_STRING_JOIN(s)
#define YH_TO_STRING_JOIN(s) #s

#endif //YH_YHMACROS_H_