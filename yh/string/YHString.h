#ifndef YH_STRING_STRING_H_
#define YH_STRING_STRING_H_

#include "../YHMacros.h"

#if (YH_TARGET_PLATFORM == YH_PLATFORM_BLACKBERRY)
#include <string.h>
#endif

#include <stdarg.h>
#include <string>
#include <functional>
#include <sstream>
#include <vector>

#include "../base/Ref.h"

NS_YH_BEGIN


class YHString : public Ref
{
public:

    YHString();

    YHString(const char* str);

    YHString(const std::string& str);

    YHString(const YHString& str);

    virtual ~YHString();
    
    /** 
     *override assignment operator
     */
    YHString& operator= (const YHString& other);

    /** 
     * init a string with format, it's similar with the c function 'sprintf'
     */
    bool initWithFormat(const char* format, ...);

    /** convert to int value 
     * 
     */
    int intValue() const;

    /** convert to unsigned int value 
     * 
     */
    unsigned int uintValue() const;

	/** convert to int64 value
	*
	*/
	int64_t longValue() const;

	/** convert to unsigned int64 value
	*
	*/
	uint64_t ulongValue() const;

    /** convert to float value 
     * 
     */
    float floatValue() const;

    /** convert to double value 
     * 
     */
    double doubleValue() const;

    /** convert to bool value 
     * 
     */
    bool boolValue() const;

    /** get the C string 
     * 
     */
    const char* getCString() const;

    /** get the length of string 
     * 
     */
    int length() const;

    /** compare to a c string 
     * 
     */
    int compare(const char *) const;

    /** append additional characters at the end of its current value 
     * 
     * 
     */
    void append(const std::string& str);

    /** append(w/ format) additional characters at the end of its current value 
     * 
     * 
     */
    void appendWithFormat(const char* format, ...);

    /** split a string 
     * 
     * 
     */
    std::vector<std::string> componentsSeparatedByString(const char *delimiter);
    
    /* override functions 
     * 
     */
    virtual bool isEqual(const Ref* pObject);

    /** create a string with std string, you can also pass a c string pointer because the default constructor of std::string can access a c string pointer. 
     *  @return A YHString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * 
     */
    static YHString* create(const std::string& str);

    /** create a string with format, it's similar with the c function 'sprintf', the default buffer size is (1024*100) bytes,
     *  if you want to change it, you should modify the kMax__StringLen macro in YHString.cpp file.
     *  @return A YHString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * 
     */
    static YHString* createWithFormat(const char* format, ...);

    /** create a string with binary data 
     *  @return A YHString pointer which is an autorelease object pointer,
     *          it means that you needn't do a release operation unless you retain it.
     * 
     */
    static YHString* createWithData(const unsigned char* pData, int nLen);

    /**
     * 
     * 
     */
    virtual YHString* clone() const;
    
private:

    /** only for internal use */
    bool initWithFormatAndValist(const char* format, va_list ap);

public:
    std::string _string;
};

struct StringCompare : public std::binary_function<YHString *, YHString *, bool> {
    public:
        bool operator() (YHString * a, YHString * b) const {
            return strcmp(a->getCString(), b->getCString()) < 0;
        }
};

#define StringMake(str) YHString::create(str)
#define ccs             StringMake

class StringUtils
{
public:
    
    template<typename T>
    static std::string toString(T arg)
    {
        std::stringstream ss;
        ss << arg;
        return ss.str();
    }
    
    static std::string format(const char* format, ...)
    {
        #define YH_MAX_STRING_LENGTH (1024*100)
        
        std::string ret;
        
        va_list ap;
        va_start(ap, format);
        
        char* buf = (char*)malloc(YH_MAX_STRING_LENGTH);
        if (buf != NULL)
        {
            vsnprintf(buf, YH_MAX_STRING_LENGTH, format, ap);
            ret = buf;
            free(buf);
        }
        va_end(ap);
        
        return ret;
    }
    
    static std::vector<std::string> split(const std::string& str,const char *delimiter)
    {
        std::vector<std::string> result;
        std::string strTmp = str;
        size_t cutAt;
        while( (cutAt = strTmp.find_first_of(delimiter)) != strTmp.npos )
        {
            if(cutAt > 0)
            {
                result.push_back(strTmp.substr(0, cutAt));
            }
            strTmp = strTmp.substr(cutAt + 1);
        }
        
        if(strTmp.length() > 0)
        {
            result.push_back(strTmp);
        }
        return result;
    }
};

NS_YH_END

#endif //YH_STRING_STRING_H_
