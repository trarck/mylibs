
#include <iostream>
#include <yh/base/Object.h>
#include <yh/base/Internals.h>
#include <yh/io/Buffer.h>

#define printDebugMsg(format, ...) \
printf( "[%s]" format " File:%s, Line:%d\n", __FUNCTION__,##__VA_ARGS__, __FILE__, __LINE__ );

USING_NS_YH;

class TestObject:public yh::Object
{
public:
    TestObject(){
        printDebugMsg("TestObject create\n");
    }
    ~TestObject(){
        printf("TestObject destroy\n");
    }
};

void printBuf(unsigned char* buf,size_t size){
    printf("buf:");
    for (int i=0; i<size; ++i) {
        printf(" %02x",*(buf+i));
    }
    printf("\n");
}


int main(int argc, const char * argv[])
{
    TestObject t;
    
    Buffer* buf=new Buffer(4);
    
    unsigned char* pData=buf->getData();
    
    *(pData)=0x01;
    *(pData+1)=0x02;
    *(pData+2)=0x03;
    *(pData+3)=0x04;
    
    uint8_t ui8=0;
    
    for (int i=0; i<4; i++) {
        buf->readUInt8(i, &ui8);
        printf("%u\n",ui8);
    }
    
    
    printf("--------u16--------\n");
    uint16_t ui16=0;
    
    for (int i=0; i<2; i++) {
        ui16=0;
        buf->readUInt16(i*2+1, &ui16);
        printf("%04x\n",ui16);
    }
    
    return 0;
}

