#ifndef YH_PLATFORM_STDC_LINUX_H_
#define YH_PLATFORM_STDC_LINUX_H_

#include "../CCPlatformConfig.h"
#if YH_TARGET_PLATFORM == YH_PLATFORM_LINUX

#include "../CCPlatformMacros.h"

#include <float.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <stdint.h>
#include <limits.h>

#ifndef MIN
#define MIN(x,y) (((x) > (y)) ? (y) : (x))
#endif  // MIN

#ifndef MAX
#define MAX(x,y) (((x) < (y)) ? (y) : (x))
#endif  // MAX

// some function linux do not have
#define tanf tan
#define sqrtf sqrt
#define cosf cos
#define sinf sin

#endif // YH_TARGET_PLATFORM == YH_PLATFORM_LINUX

#endif  // YH_PLATFORM_STDC_LINUX_H_
