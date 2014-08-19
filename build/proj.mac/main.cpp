
#include <iostream>
#include <yh/yh.h>

#include "tests/io/test_buffer.h"
#include <yh/shell/OptionParser.h>

USING_NS_YH;

using namespace yh::cli;
using namespace yh::cli::detail;

int main(int argc, const char * argv[])
{
    
    typedef ds::LinkedList<int> List;
    
    List a;
    
    a.push_back(1);
    a.push_back(2);
    
    List b;
    b=a;
    
    printf("b:%ld",a.size());
    
    printf("\n");
    return 0;
}

