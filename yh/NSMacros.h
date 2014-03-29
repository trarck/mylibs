#ifndef YH_NSMACROS_H_
#define YH_NSMACROS_H_

#ifdef __cplusplus

#define NS_YH_BEGIN                     namespace yh {
#define NS_YH_END                       }
#define USING_NS_YH                     using namespace yh

#else

#define NS_YH_BEGIN                     
#define NS_YH_END                       
#define USING_NS_YH

#endif
	
#endif //YH_NSMACROS_H_