#include "YHString.h"
#include <stdlib.h>
#include <stdio.h>
#include "../platform/Log.h"

NS_YH_BEGIN

#define kMaxStringLen (1024*100)

YHString::YHString()
:_string("")
{}

YHString::YHString(const char * str)
    :_string(str)
{}

YHString::YHString(const std::string& str)
    :_string(str)
{}

YHString::YHString(const YHString& str)
    :_string(str.getCString())
{}

YHString::~YHString()
{
    YHDEBUG("deallocing YHString: %p", this);

    _string.clear();
}

YHString& YHString::operator= (const YHString& other)
{
    if (this != &other) {
        _string = other._string;
    }
    return *this;
}

bool YHString::initWithFormatAndValist(const char* format, va_list ap)
{
    bool bRet = false;
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        _string = pBuf;
        free(pBuf);
        bRet = true;
    }
    return bRet;
}

bool YHString::initWithFormat(const char* format, ...)
{
    bool bRet = false;
    _string.clear();

    va_list ap;
    va_start(ap, format);

    bRet = initWithFormatAndValist(format, ap);

    va_end(ap);

    return bRet;
}

int YHString::intValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return atoi(_string.c_str());
}

unsigned int YHString::uintValue() const
{
    if (length() == 0)
    {
        return 0;
    }
    return (unsigned int)atoi(_string.c_str());
}

float YHString::floatValue() const
{
    if (length() == 0)
    {
        return 0.0f;
    }
    return (float)atof(_string.c_str());
}

double YHString::doubleValue() const
{
    if (length() == 0)
    {
        return 0.0;
    }
    return atof(_string.c_str());
}

bool YHString::boolValue() const
{
    if (length() == 0)
    {
        return false;
    }

    if (_string=="0" || _string== "false")
    {
        return false;
    }
    return true;
}

const char* YHString::getCString() const
{
    return _string.c_str();
}

int YHString::length() const
{
    return static_cast<int>(_string.length());
}

int YHString::compare(const char * pStr) const
{
    return strcmp(getCString(), pStr);
}

void YHString::append(const std::string& str)
{
    _string.append(str);
}

void YHString::appendWithFormat(const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    
    char* pBuf = (char*)malloc(kMaxStringLen);
    if (pBuf != NULL)
    {
        vsnprintf(pBuf, kMaxStringLen, format, ap);
        _string.append(pBuf);
        free(pBuf);
    }
    
    va_end(ap);
    
}

std::vector<std::string> YHString::componentsSeparatedByString(const char *delimiter)
{
    std::vector<std::string> result;
    std::string strTmp = _string;
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

bool YHString::isEqual(const Object* pObject)
{
    bool bRet = false;
    const YHString* pStr = dynamic_cast<const YHString*>(pObject);
    if (pStr != NULL)
    {
        if (0 == _string.compare(pStr->_string))
        {
            bRet = true;
        }
    }
    return bRet;
}

YHString* YHString::create(const std::string& str)
{
    YHString* ret = new YHString(str);
//    ret->autorelease();
    return ret;
}

YHString* YHString::createWithData(const unsigned char* data, int nLen)
{
    YHString* ret = NULL;
    if (data != NULL)
    {
        char* pStr = (char*)malloc(nLen+1);
        if (pStr != NULL)
        {
            pStr[nLen] = '\0';
            if (nLen > 0)
            {
                memcpy(pStr, data, nLen);
            }
            
            ret = YHString::create(pStr);
            free(pStr);
        }
    }
    return ret;
}

YHString* YHString::createWithFormat(const char* format, ...)
{
    YHString* ret = YHString::create("");
    va_list ap;
    va_start(ap, format);
    ret->initWithFormatAndValist(format, ap);
    va_end(ap);

    return ret;
}

//YHString* YHString::createWithContentsOfFile(const char* filename)
//{
////    std::string str = FileUtils::getInstance()->getStringFromFile(filename);
////    return YHString::create(std::move(str));
//}


YHString* YHString::clone() const
{
    return YHString::create(_string);
}

NS_YH_END
