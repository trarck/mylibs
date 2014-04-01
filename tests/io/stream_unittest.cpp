
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test input stream
TEST(StreamTest, InputStream) {
    
    unsigned char buf[]={
        0x12,
        0x34,0x56,
        0x12,0x34,0x56,0x78,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,//15
        
        0xFC,// signed -4
        0xFF,0xFC,
        0xFF,0xFF,0xFF,0xFC,//22
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//30
        
        0x56,0x40,//float16 100
        
        0x42,0xC8,0x00,0x00,//float 100
        
        0x40,0x59,0x00,0x00,0x00,0x00,0x00,0x00//double 100
    };
    
    
    int bufferSize=sizeof(buf);
    
    Buffer* buffer=new Buffer(buf,bufferSize);
    
    InputStream* ins=new InputStream();
    ins->init(buffer);
    ins->setEndianness(kBigEndian);
    
    uint8_t u8=ins->readUInt8();
    EXPECT_EQ(0x12, u8);
    
    uint16_t u16=ins->readUInt16();
    EXPECT_EQ(0x3456, u16);
    
    uint32_t u32=ins->readUInt32();
    EXPECT_EQ(0x12345678, u32);
    
    uint64_t u64=ins->readUInt64();
    EXPECT_EQ(0x1122334455667788, u64);
    
    int8_t i8=ins->readInt8();
    EXPECT_EQ(-4, i8);
    
    int16_t i16=ins->readInt16();
    EXPECT_EQ(-4, i16);
    
    int32_t i32=ins->readInt32();
    EXPECT_EQ(-4, i32);
    
    int64_t i64=ins->readInt64();
    EXPECT_EQ(-4, i64);
    
    float f16=ins->readHalfFloat();
    EXPECT_EQ(100.0f, f16);
    
    float f32=ins->readFloat();
    EXPECT_EQ(100.0f, f32);
    
    double f64=ins->readDouble();
    EXPECT_EQ(100.0f, f64);
    
    ins->release();
    
    buffer->release();
    
}

TEST(StreamTest, OutputStream) {
    
    unsigned char buf[]={
        0x12,
        0x34,0x56,
        0x12,0x34,0x56,0x78,
        0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,//15
        
        0xFC,// signed -4
        0xFF,0xFC,
        0xFF,0xFF,0xFF,0xFC,//22
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//30
        
        0x56,0x40,//float16 100
        
        0x42,0xC8,0x00,0x00,//float 100
        
        0x40,0x59,0x00,0x00,0x00,0x00,0x00,0x00//double 100
    };
    
    
    int bufferSize=sizeof(buf);
    
    Buffer* buffer=new Buffer(bufferSize);
    
    OutputStream* outs=new OutputStream();
    outs->init(buffer);
    outs->setEndianness(kBigEndian);
    
    outs->writeUInt8(0x12);
    outs->writeUInt16(0x3456);
    outs->writeUInt32(0x12345678);
    outs->writeUInt64(0x1122334455667788);
    
    outs->writeInt8(-4);
    outs->writeInt16(-4);
    outs->writeInt32(-4);
    outs->writeInt64(-4);
    
    outs->writeHalfFloat(100);
    outs->writeFloat(100);
    outs->writeDouble(100);
    
    //check buffer content
    unsigned char* pData=buffer->getData();
    
//    for (int i=0; i<bufferSize; ++i) {
//        printf("%x,",*(pData+i));
//    }
//    printf("\n");
    
    for (int i=0; i<bufferSize; ++i) {
        EXPECT_EQ(buf[i], *(pData+i))<<"i="<<i;
    }
    
    outs->release();
    
    buffer->release();
    
}
