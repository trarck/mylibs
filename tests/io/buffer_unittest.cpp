
#include <stdio.h>
#include <yh/yh.h>

USING_NS_YH;

template <typename T>
void testAssert(T v1,T v2,const std::string& msg)
{
    if (v1!=v2) {
        printf("test fail:%s\n",msg.c_str());
    }
}


int testBigEndian()
{
    YHDEBUG("**********test big Endian start**********");
    
#define BUFFER_SIZE 23
    
    Buffer* buffer=new Buffer(BUFFER_SIZE);
    
    unsigned char buf[BUFFER_SIZE]={
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//for uint 252 int -4
        
        0x56,0x40,//float16 100
        
        0x42,0xC8,0x00,0x00,//float 100
        
        0x40,0x59,0x00,0x00,0x00,0x00,0x00,0x00,//double 100
        
        0x00
    };
    
    buffer->writeBytes(0,buf,BUFFER_SIZE);
    
    
    uint8_t u8=buffer->readUInt8(7);
    testAssert<uint8_t>(u8,0xFC,"test uint8");
    
    uint16_t u16be=buffer->readUInt16BE(6);
    testAssert<uint16_t>(u16be,0xFFFC,"test uint16");
    
    uint32_t u32be=buffer->readUInt32BE(4);
    testAssert<uint32_t>(u32be,0xFFFFFFFC,"test uint32");
    
    uint64_t u64be=buffer->readUInt64BE(0);
    testAssert<uint64_t>(u64be,0xFFFFFFFFFFFFFFFC,"test uint64");
    
    int8_t i8=buffer->readInt8(7);
    testAssert<int8_t>(i8,-4,"test int8");
    
    int16_t i16be=buffer->readInt16BE(6);
    testAssert<int16_t>(i16be,-4,"test int16");
    
    int32_t i32be=buffer->readInt32BE(4);
    testAssert<int32_t>(i32be,-4,"test int32");
    
    int64_t i64be=buffer->readInt64BE(0);
    testAssert<int64_t>(i64be,-4,"test int64");
    
    float halfFloat=buffer->readFloat16BE(8);
    testAssert<float>(halfFloat,100.0f,"test half float");
    
    float singleFloat=buffer->readFloatBE(10);
    testAssert<float>(singleFloat,100.0f,"test single float");
    
    double doubleFloat=buffer->readDoubleBE(14);
    testAssert<double>(doubleFloat,100.0f,"test double float");
    
    buffer->release();
    
    
    YHDEBUG("**********test big Endian end**********");
    
    return 1;
}


int testLittleEndian()
{
    YHDEBUG("**********test little Endian start**********");
  
#define BUFFER_SIZE_L 23
    
    Buffer* buffer=new Buffer(BUFFER_SIZE);
    
    unsigned char buf[BUFFER_SIZE]={
        0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//for uint 252 int -4

        0x40,0x56,//float16 100
        
        0x00,0x00,0xC8,0x42,//float 100
        
        0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40,//double 100
        
        
        0x00
    };
    
    buffer->writeBytes(0,buf,BUFFER_SIZE);
    
    
    uint8_t u8=buffer->readUInt8(0);
    testAssert<uint8_t>(u8,0xFC,"test uint8");
    
    uint16_t u16le=buffer->readUInt16LE(0);
    testAssert<uint16_t>(u16le,0xFFFC,"test uint16");
    
    uint32_t u32le=buffer->readUInt32LE(0);
    testAssert<uint32_t>(u32le,0xFFFFFFFC,"test uint32");
    
    uint64_t u64le=buffer->readUInt64LE(0);
    testAssert<uint64_t>(u64le,0xFFFFFFFFFFFFFFFC,"test uint64");
    
    int8_t i8=buffer->readInt8(0);
    testAssert<int8_t>(i8,-4,"test int8");
    
    int16_t i16le=buffer->readInt16LE(0);
    testAssert<int16_t>(i16le,-4,"test int16");
    
    int32_t i32le=buffer->readInt32LE(0);
    testAssert<int32_t>(i32le,-4,"test int32");
    
    int64_t i64le=buffer->readInt64LE(0);
    testAssert<int64_t>(i64le,-4,"test int64");
    
    
    float halfFloat=buffer->readFloat16LE(8);
    testAssert<float>(halfFloat,100.0f,"test half float");
    
    float singleFloat=buffer->readFloatLE(10);
    testAssert<float>(singleFloat,100.0f,"test single float");
    
    double doubleFloat=buffer->readDoubleLE(14);
    testAssert<double>(doubleFloat,100.0f,"test double float");
    
    buffer->release();
    
    
    YHDEBUG("**********test little Endian end**********");
    
    return 1;
}

int testBuffer()
{
    YHDEBUG("**********test buffer**********");

    
    testBigEndian();
    
    testLittleEndian();
    
    return 1;
}

int testBufferPerfermens()
{
    YHDEBUG("**********test buffer perfermens**********");
    
    
	Buffer* buffer=new Buffer(42);
    
    unsigned char buf[42]={
        0x01,0x02,0x03,0x04,
        0x05,0x06,0x07,0x08,
        0x09,0x0A,0x0B,0x0C,
        0xFF,//-1
        0xFC,0xFF,//16le -4
        0xFF,0xFC,//16be -4
        
        0xFC,0xFF,0xFF,0xFF,//32le -4
        0xFF,0xFF,0xFF,0xFC,//32be -4
        
        0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//64le -4
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//64be -4
        
        
        
        0x00
    };
    
    buffer->writeBytes(0,buf,100);
    
    struct timeval start;
    
    struct timeval end;
    
    int n=10000000;
    uint32_t u32le;
    
    gettimeofday(&start, 0);
    for (int i=0; i<n; ++i) {
        u32le=buffer->readUInt32LE(i%38);
    }
    
    gettimeofday(&end, 0);
    
    printf("use:%ld,%d\n",end.tv_sec-start.tv_sec,end.tv_usec-start.tv_usec);
    
    gettimeofday(&start, 0);
    for (int i=0; i<n; ++i) {
        u32le=buffer->readUInt32LE2(i%38);
    }
    
    gettimeofday(&end, 0);
    
    printf("use:%ld,%d\n",end.tv_sec-start.tv_sec,end.tv_usec-start.tv_usec);
    
    
    buffer->release();
    
    return 1;
}


