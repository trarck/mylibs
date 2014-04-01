
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(BufferTest, ReadBigEndian) {
    
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
    EXPECT_EQ(u8,0xFC);
    
    uint16_t u16=buffer->readUInt16BE(6);
    EXPECT_EQ(u16,0xFFFC);
    
    uint32_t u32=buffer->readUInt32BE(4);
    EXPECT_EQ(u32,0xFFFFFFFC);
    
    uint64_t u64=buffer->readUInt64BE(0);
    EXPECT_EQ(u64,0xFFFFFFFFFFFFFFFC);
    
    int8_t i8=buffer->readInt8(7);
    EXPECT_EQ(i8,-4);
    
    int16_t i16=buffer->readInt16BE(6);
    EXPECT_EQ(i16,-4);
    
    int32_t i32=buffer->readInt32BE(4);
    EXPECT_EQ(i32,-4);
    
    int64_t i64=buffer->readInt64BE(0);
    EXPECT_EQ(i64,-4);
    
    float halfFloat=buffer->readFloat16BE(8);
    EXPECT_EQ(halfFloat,100);
    
    float singleFloat=buffer->readFloatBE(10);
    EXPECT_EQ(singleFloat,100);
    
    double doubleFloat=buffer->readDoubleBE(14);
    EXPECT_EQ(doubleFloat,100);
    
    buffer->release();
    
}

TEST(BufferTest, ReadLittleEndian) {
    
#define BUFFER_SIZE_L 23
    
    Buffer* buffer=new Buffer(BUFFER_SIZE_L);
    
    unsigned char buf[BUFFER_SIZE]={
        0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//for uint 252 int -4
        
        0x40,0x56,//float16 100
        
        0x00,0x00,0xC8,0x42,//float 100
        
        0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40,//double 100
        
        
        0x00
    };
    
    buffer->writeBytes(0,buf,BUFFER_SIZE_L);
    
    
    uint8_t u8=buffer->readUInt8(0);
    EXPECT_EQ(u8,0xFC);
    
    uint16_t u16=buffer->readUInt16LE(0);
    EXPECT_EQ(u16,0xFFFC);
    
    uint32_t u32=buffer->readUInt32LE(0);
    EXPECT_EQ(u32,0xFFFFFFFC);
    
    uint64_t u64=buffer->readUInt64LE(0);
    EXPECT_EQ(u64,0xFFFFFFFFFFFFFFFC);
    
    int8_t i8=buffer->readInt8(0);
    EXPECT_EQ(i8,-4);
    
    int16_t i16=buffer->readInt16LE(0);
    EXPECT_EQ(i16,-4);
    
    int32_t i32=buffer->readInt32LE(0);
    EXPECT_EQ(i32,-4);
    
    int64_t i64=buffer->readInt64LE(0);
    EXPECT_EQ(i64,-4);
    
    
    float halfFloat=buffer->readFloat16LE(8);
    EXPECT_EQ(halfFloat,100);
    
    float singleFloat=buffer->readFloatLE(10);
    EXPECT_EQ(singleFloat,100);
    
    double doubleFloat=buffer->readDoubleLE(14);
    EXPECT_EQ(doubleFloat,100);
    
    buffer->release();
}

//test write
TEST(BufferTest, writeBigEndian) {
    
    
    unsigned char buf[]={
        0x12,
        0x34,0x56,
        0x12,0x34,0x56,0x78,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,//15
        
        0xFC,
        0xFF,0xFC,
        0xFF,0xFF,0xFF,0xFC,//22
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//30
        
        0x56,0x40,//float16 100
        
        0x42,0xC8,0x00,0x00,//float 100
        
        0x40,0x59,0x00,0x00,0x00,0x00,0x00,0x00//double 100
        
    };
    
    int buffSize=sizeof(buf);
    
    Buffer* buffer=new Buffer(buffSize);
    
    int pos=0;
    
    pos+=buffer->writeUInt8(0x12, pos);
    pos+=buffer->writeUInt16BE(0x3456, pos);
    pos+=buffer->writeUInt32BE(0x12345678, pos);
    pos+=buffer->writeUInt64BE(0x1122334455667788, pos);
    
    pos+=buffer->writeInt8(-4, pos);
    pos+=buffer->writeInt16BE(-4, pos);
    pos+=buffer->writeInt32BE(-4, pos);
    pos+=buffer->writeInt64BE(-4, pos);
    
    pos+=buffer->writeFloat16BE(100, pos);
    pos+=buffer->writeFloatBE(100, pos);
    pos+=buffer->writeDoubleBE(100, pos);
    
    //check buffer content
    unsigned char* pData=buffer->getData();
    
//    for (int i=0; i<buffSize; ++i) {
//        printf("%x,",*(pData+i));
//    }
//    printf("\n");
    
    for (int i=0; i<buffSize; ++i) {
//        printf("%x,",buf[i]);
        EXPECT_EQ(buf[i], *(pData+i))<<"i="<<i;
    }
    
    buffer->release();
    
}

TEST(BufferTest, writeLittleEndian) {
    
    
    unsigned char buf[]={
        0x12,
        0x56,0x34,
        0x78,0x56,0x34,0x12,
        0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,//15
        
        0xFC,
        0xFC,0xFF,
        0xFC,0xFF,0xFF,0xFF,//22
        0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//30
        
        0x40,0x56,//float16 100
        
        0x00,0x00,0xC8,0x42,//float 100
        
        0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40//double 100
        
    };
    
    int buffSize=sizeof(buf);
    
    Buffer* buffer=new Buffer(buffSize);
    
    int pos=0;
    
    pos+=buffer->writeUInt8(0x12, pos);
    pos+=buffer->writeUInt16LE(0x3456, pos);
    pos+=buffer->writeUInt32LE(0x12345678, pos);
    pos+=buffer->writeUInt64LE(0x1122334455667788, pos);
    
    pos+=buffer->writeInt8(-4, pos);
    pos+=buffer->writeInt16LE(-4, pos);
    pos+=buffer->writeInt32LE(-4, pos);
    pos+=buffer->writeInt64LE(-4, pos);
    
    pos+=buffer->writeFloat16LE(100, pos);
    pos+=buffer->writeFloatLE(100, pos);
    pos+=buffer->writeDoubleLE(100, pos);
    
    //check buffer content
    unsigned char* pData=buffer->getData();
    
//    for (int i=0; i<buffSize; ++i) {
//        printf("%x,",*(pData+i));
//    }
//    
//    printf("\n");
    
    for (int i=0; i<buffSize; ++i) {
        //        printf("%x,",buf[i]);
        EXPECT_EQ(buf[i], *(pData+i))<<"i="<<i;
    }
    
    buffer->release();
    
}
