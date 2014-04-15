#include "Plist2.h"

NS_YH_BEGIN

Json::Value Plist2::getDataFromFile(const std::string& file)
{
    pugi::xml_document doc;
    
    if(doc.load_file(file.c_str())){
        
        return getDataFromDocument(doc);
        
    }
    
    return Json::Value::null;
}

Json::Value Plist2::getDataFromContent(const std::string& content)
{
    pugi::xml_document doc;
    
    if (doc.load(content.c_str())) {
        
        return getDataFromDocument(doc);
    }
    
    return Json::Value::null;
}

/*
 <Plist2 version="1.0">
 <array>
 
 </array>
 </Plist2>
 
 */
Json::Value Plist2::getDataFromDocument(const pugi::xml_document& doc)
{
    
    Json::Value root;
    
    //xml first element is Plist2
    //Plist2 only have one child array|dict
    
    pugi::xml_node rootNode=doc.first_child().first_child();
    
    std::string rootName=rootNode.name();
    
    if (rootName=="array") {

//        parseArray(rootNode, root);
        addArray(rootNode, root);
        
    }else if (rootName=="dict"){
//        parseDict(rootNode, root);
        addDict(rootNode, root);
    }
    
    while (elems.size()) {
        
        Elem ele=elems.back();
        
        elems.pop_back();
        
        if (ele.type==kArrayElement) {
            
            parseArray(ele.node, *(ele.value));
            
        }else if (ele.type==kDictElement){
            parseDict(ele.node, *(ele.value));
        }
    }

    return root;
}

void Plist2::parseArray(pugi::xml_node& node,Json::Value& arrayValue)
{
    for (pugi::xml_node elem=node.first_child(); elem; elem=elem.next_sibling()) {
        parseArrayElement(elem, arrayValue);
    }
}

void Plist2::parseDict(pugi::xml_node& node,Json::Value& dictValue)
{
    for (pugi::xml_node elem=node.first_child(); elem; elem=elem.next_sibling()) {
        parseDictElement(elem, dictValue);
    }
}


void Plist2::parseArrayElement(pugi::xml_node& element,Json::Value& arrayValue)
{
    parseValue(element, arrayValue[arrayValue.size()]);
}

void Plist2::parseDictElement(pugi::xml_node& element,Json::Value& dictValue)
{
    //first element is key
    const char* key=element.text().get();
    
    element=element.next_sibling();
    
    parseValue(element, dictValue[key]);

}


void Plist2::parseValue(pugi::xml_node &valueNode, Json::Value &outValue)
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
        addArray(valueNode, outValue);
    }else if (valueName=="dict"){
        addDict(valueNode, outValue);
    }
}

void Plist2::addArray(pugi::xml_node& node,Json::Value& arrayValue)
{
    Elem ele={node,&arrayValue,kArrayElement};
    elems.push_back(ele);
}

void Plist2::addDict(pugi::xml_node& node,Json::Value& dictValue)
{
    Elem ele={node,&dictValue,kDictElement};
    elems.push_back(ele);
}

NS_YH_END
