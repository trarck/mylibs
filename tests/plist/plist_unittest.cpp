
#include <stdio.h>
#include <yh/yh.h>
#include <yh/plist/Plist.h>
#include <yh/plist/PlistRecursion.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(Plist, read) {

	Plist plist;

	timeval start, end;

	getTimeofday(&start, 0);

	for (int i = 0; i < 100; ++i) {
		Json::Value data = plist.getDataFromFile("/Users/duanhouhai/development/trarck/mylibs/tests/plist/0.plist");
	}
	getTimeofday(&end, 0);

	printf("use:%ld,%d\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);
}

TEST(Plist, read2) {

	PlistRecursion plist;

	struct timeval start, end;

	getTimeofday(&start, NULL);

	for (int i = 0; i < 100; ++i)
	{
		Json::Value data = plist.getDataFromFile("/Users/duanhouhai/development/trarck/mylibs/tests/plist/0.plist");
	}

	getTimeofday(&end, NULL);

	printf("use:%ld,%d\n", end.tv_sec - start.tv_sec, end.tv_usec - start.tv_usec);

	//    std::cout<<data<<std::endl;

}
