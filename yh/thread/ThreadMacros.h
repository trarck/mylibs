#ifndef YH_IO_BINARYMACROS_H_
#define YH_IO_BINARYMACROS_H_

#ifdef __cplusplus

#define NS_YH_THEAD_BEGIN                     namespace yh { namespace thread {
#define NS_YH_THEAD_END                       }}
#define USING_NS_YH_THEAD                     using namespace yh::thread

#else

#define NS_YH_THEAD_BEGIN                     
#define NS_YH_THEAD_END                       
#define USING_NS_THEAD_YH

#endif

#endif //YH_IO_BINARYMACROS_H_