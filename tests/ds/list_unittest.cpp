
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(LinkedList, Default) {
    
    ds::LinkedList<int> myList;
    
    for (int i=0; i<4; ++i) {
        myList.push_back(i+1);
    }
    
    for(ds::LinkedList<int>::Iterator iter=myList.begin();iter!=myList.end();++iter){
        printf("%d\n",*iter);
    }
    
    
}
