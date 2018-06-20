#ifndef YH_THREAD_THREADMACROS_H_
#define YH_THREAD_THREADMACROS_H_

#ifdef __cplusplus

#define NS_YH_THREAD_BEGIN                     namespace yh { namespace thread {
#define NS_YH_THREAD_END                       }}
#define USING_NS_YH_THREAD                     using namespace yh::thread

#else

#define NS_YH_THREAD_BEGIN                     
#define NS_YH_THREAD_END                       
#define USING_NS_THREAD_YH

#endif

#endif //YH_THREAD_THREADMACROS_H_