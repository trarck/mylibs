#ifndef YH_PLIST_PLISTPLISTRECURSION_H_
#define YH_PLIST_PLISTPLISTRECURSION_H_

#include "../base/Ref.h"
#include "../jsoncpp/json.h"
#include "../pugixml/pugixml.hpp"

NS_YH_BEGIN

class PlistRecursion
{
public:
	
    Json::Value getDataFromFile(const std::string& file);

    Json::Value getDataFromContent(const std::string& content);
    
    Json::Value getDataFromDocument(const pugi::xml_document& doc);

protected:

    void parseArray(pugi::xml_node& node,Json::Value& arrayValue);
    
    void parseDict(pugi::xml_node& node,Json::Value& dictValue);
    
    void parseArrayElement(pugi::xml_node& element,Json::Value& arrayValue);
    
    void parseDictElement(pugi::xml_node& element,Json::Value& dictValue);
    
    void parseValue(pugi::xml_node& valueNode,Json::Value& outValue);

};


NS_YH_END

#endif // YH_PLIST_PLISTPLISTRECURSION_H_
