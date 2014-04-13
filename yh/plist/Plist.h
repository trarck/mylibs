#ifndef YH_PLIST_PLIST_H_
#define YH_PLIST_PLIST_H_

#include <yh/base/Object.h>
#include <yh/jsoncpp/json.h>


NS_YH_BEGIN

class Plist
{
public:
	
    Json::Value getDataFromFile(const std::string& file);

    Json::Value getDataFromContent(const std::string& content);

protected:



};


NS_YH_END

#endif // YH_PLIST_PLIST_H_
