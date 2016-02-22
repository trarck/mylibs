#ifndef YH_PLIST_PLIST2_H_
#define YH_PLIST_PLIST2_H_

#include "../base/Object.h"
#include "../jsoncpp/json.h"
#include "../pugixml/pugixml.hpp"

NS_YH_BEGIN

enum ElemType {
    kArrayElement = 1,
    kDictElement = 2
};

struct Elem
{
    pugi::xml_node node;
    Json::Value* value;
    ElemType type;
};

class Plist2
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
    
    void addArray(pugi::xml_node& node,Json::Value& arrayValue);
    
    void addDict(pugi::xml_node& node,Json::Value& dictValue);
    
protected:
    
    std::vector<Elem> elems;

};


NS_YH_END

#endif // YH_PLIST_PLIST2_H_
