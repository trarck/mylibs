#include "PlistRecursion.h"
#include <stdlib.h>

NS_YH_BEGIN

Json::Value PlistRecursion::getDataFromFile(const std::string& file)
{
    pugi::xml_document doc;
    
    if(doc.load_file(file.c_str())){
        
        return getDataFromDocument(doc);
        
    }
    
    return Json::Value::null;
}

Json::Value PlistRecursion::getDataFromContent(const std::string& content)
{
    pugi::xml_document doc;
    
    if (doc.load(content.c_str())) {
        
        return getDataFromDocument(doc);
    }
    
    return Json::Value::null;
}

/*
 <plist version="1.0">
 <array>
 
 </array>
 </plist>
 
 */
Json::Value PlistRecursion::getDataFromDocument(const pugi::xml_document& doc)
{
    
    Json::Value root;
    
    //xml first element is plist
    //plist only have one child array|dict
    
    pugi::xml_node rootNode=doc.first_child().first_child();
    
    std::string rootName=rootNode.name();
    
    if (rootName=="array") {

        parseArray(rootNode, root);
        
    }else if (rootName=="dict"){
        parseDict(rootNode, root);
    }

    return root;
}

void PlistRecursion::parseArray(pugi::xml_node& node,Json::Value& arrayValue)
{
    for (pugi::xml_node elem=node.first_child(); elem; elem=elem.next_sibling()) {
        parseArrayElement(elem, arrayValue);
    }
}

void PlistRecursion::parseDict(pugi::xml_node& node,Json::Value& dictValue)
{
    for (pugi::xml_node elem=node.first_child(); elem; elem=elem.next_sibling()) {
        parseDictElement(elem, dictValue);
    }
}


void PlistRecursion::parseArrayElement(pugi::xml_node& element,Json::Value& arrayValue)
{
    parseValue(element, arrayValue[arrayValue.size()]);
}

void PlistRecursion::parseDictElement(pugi::xml_node& element,Json::Value& dictValue)
{
    //first element is key
    const char* key=element.text().get();
    
    element=element.next_sibling();
    
    parseValue(element, dictValue[key]);

}


void PlistRecursion::parseValue(pugi::xml_node &valueNode, Json::Value &outValue)
{
    
    std::string valueName=valueNode.name();
    
    const pugi::char_t* text=valueNode.text().get();
    
    //ignore date
    if (valueName=="integer") {
        outValue=Json::Value(atoi(text));
    }else if(valueName=="real"){
        outValue=Json::Value(atof(text));
    }else if (valueName=="true"){
        outValue=Json::Value(true);
    }else if (valueName=="false"){
        outValue=Json::Value(false);
    }else if (valueName=="string" || valueName=="data" || valueName=="date"){
        outValue=Json::Value(text);
    }else if (valueName=="array"){
        parseArray(valueNode, outValue);
    }else if (valueName=="dict"){
        parseDict(valueNode, outValue);
    }
}

NS_YH_END
