
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(Pugixml, read) {
    const char source[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\
    <plist version=\"1.0\">\
    <dict>\
    <key>a</key>\
    <integer>1</integer>\
    <key>b</key>\
    <integer>2</integer>\
	</dict>\
    </plist>";
    
    size_t size = sizeof(source);
    //]
    
    pugi::xml_document doc;
    
    {
        //[code_load_memory_buffer
        // You can use load_buffer to load document from immutable memory block:
        pugi::xml_parse_result result = doc.load_buffer(source, size);
        //]
        
        std::cout << "Load result: " << result.description() << ", root name: " << doc.first_child().first_child().name() << std::endl;
        
        
        pugi::xml_node rootNode=doc.first_child().first_child();
        
        for (pugi::xml_node elem=rootNode.first_child(); elem; elem=elem.next_sibling()) {
            
            std::string elemName=elem.name();
            
            std::cout<< "elem name:" << elemName  <<"="<< elem.text().get() << std::endl;
            
            elem.next_sibling();
            
        }
    }
}
