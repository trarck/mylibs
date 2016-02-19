#ifndef YH_PLATFORM_STDC_ANDROID_H_
#define YH_PLATFORM_STDC_ANDROID_H_

#include "../PlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID

#include "../PlatformMacros.h"
#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <cassert>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_ANDROID

#endif  // YH_PLATFORM_STDC_ANDROID_H_
