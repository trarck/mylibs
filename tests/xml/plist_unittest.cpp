
#include <stdio.h>
#include <yh/yh.h>
#include <yh/plist/Plist2.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(Plist, read) {

    Plist plist;
    
    timeval start,end;
    
    gettimeofday(&start, 0);
    
    for (int i=0; i<100; ++i) {
        Json::Value data=plist.getDataFromFile("/Users/duanhouhai/development/trarck/mylibs/tests/plist/0.plist");
    }
    gettimeofday(&end, 0);
    
    printf("use:%ld,%d\n",end.tv_sec-start.tv_sec ,end.tv_usec-start.tv_usec);
//    std::cout<<data<<std::endl;
    
}

TEST(Plist, read2) {
    
    Plist2 plist;
    
    timeval start,end;
    
    gettimeofday(&start, 0);
    
    for (int i=0; i<100; ++i) {


    Json::Value data=plist.getDataFromFile("/Users/duanhouhai/development/trarck/mylibs/tests/plist/0.plist");
    
    }
    
    gettimeofday(&end, 0);
    
    printf("use:%ld,%d\n",end.tv_sec-start.tv_sec ,end.tv_usec-start.tv_usec);
    
//    std::cout<<data<<std::endl;
    
}
