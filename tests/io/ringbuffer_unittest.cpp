
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;

//test read
TEST(RingBufferTest, ReadBigEndian) {
    
    #define BUFFER_SIZE 30
    
    RingBuffer* buffer=new RingBuffer(BUFFER_SIZE);
    
    unsigned char buf[BUFFER_SIZE]={
		0xFC,
		0xFF,0xFC,
		0xFF,0xFF,0xFF,0xFC,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,//for uint 252 int -4
        
        0x56,0x40,//float16 100
        
        0x42,0xC8,0x00,0x00,//float 100
        
        0x40,0x59,0x00,0x00,0x00,0x00,0x00,0x00,//double 100
        
        0x00
    };
    
    buffer->writeBytes(buf,BUFFER_SIZE);
    
	uint8_t u8 = buffer->readUInt8();
	EXPECT_EQ(u8, 0xFC);

	uint16_t u16 = buffer->readUInt16BE();
	EXPECT_EQ(u16, 0xFFFC);

	uint32_t u32 = buffer->readUInt32BE();
	EXPECT_EQ(u32, 0xFFFFFFFC);

    uint64_t u64=buffer->readUInt64BE();
    EXPECT_EQ(u64,0xFFFFFFFFFFFFFFFC);
       
    float halfFloat=buffer->readFloat16BE();
    EXPECT_EQ(halfFloat,100);
    
    float singleFloat=buffer->readFloatBE();
    EXPECT_EQ(singleFloat,100);
    
    double doubleFloat=buffer->readDoubleBE();
    EXPECT_LE(doubleFloat,100);
    
    buffer->release();
    
}

TEST(RingBufferTest, ReadLittleEndian) {
    
	#define BUFFER_SIZE_L 45
    
	RingBuffer* buffer=new RingBuffer(BUFFER_SIZE_L);
    
    unsigned char buf[BUFFER_SIZE_L]={
		0xFC,
		0xFC,0xFF,
		0xFC,0xFF,0xFF,0xFF,
        0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//for uint 252 int -4			//15
        
		0xFC,
		0xFC,0xFF,
		0xFC,0xFF,0xFF,0xFF,
		0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//for uint 252 int -4			//30

        0x40,0x56,//float16 100
        
        0x00,0x00,0xC8,0x42,//float 100
        
        0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40,//double 100					//44
        
        
        0x00
    };
    
    buffer->writeBytes(buf,BUFFER_SIZE_L);    
    
    uint8_t u8=buffer->readUInt8();
    EXPECT_EQ(u8,0xFC);
    
    uint16_t u16=buffer->readUInt16LE();
    EXPECT_EQ(u16,0xFFFC);
    
    uint32_t u32=buffer->readUInt32LE();
    EXPECT_EQ(u32,0xFFFFFFFC);
    
    uint64_t u64=buffer->readUInt64LE();
    EXPECT_EQ(u64,0xFFFFFFFFFFFFFFFC);
    
    int8_t i8=buffer->readInt8();
    EXPECT_EQ(i8,-4);
    
    int16_t i16=buffer->readInt16LE();
    EXPECT_EQ(i16,-4);
    
    int32_t i32=buffer->readInt32LE();
    EXPECT_EQ(i32,-4);
    
    int64_t i64=buffer->readInt64LE();
    EXPECT_EQ(i64,-4);    
    
    float halfFloat=buffer->readFloat16LE();
    EXPECT_EQ(halfFloat,100);
    
    float singleFloat=buffer->readFloatLE();
    EXPECT_EQ(singleFloat,100);
    
    double doubleFloat=buffer->readDoubleLE();
    EXPECT_EQ(doubleFloat,100);
    
    buffer->release();
}

//test write
TEST(RingBufferTest, writeBigEndian) {
    
    
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
    
	RingBuffer* buffer=new RingBuffer(buffSize);
    
    
    buffer->writeUInt8(0x12);
    buffer->writeUInt16BE(0x3456);
    buffer->writeUInt32BE(0x12345678);
    buffer->writeUInt64BE(0x1122334455667788);
    
    buffer->writeInt8(-4);
    buffer->writeInt16BE(-4);
    buffer->writeInt32BE(-4);
    buffer->writeInt64BE(-4);
    
    buffer->writeFloat16BE(100);
    buffer->writeFloatBE(100);
    buffer->writeDoubleBE(100);
    
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

TEST(RingBufferTest, writeLittleEndian) {
    
    
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
    
	RingBuffer* buffer=new RingBuffer(buffSize);
    
    buffer->writeUInt8(0x12);
    buffer->writeUInt16LE(0x3456);
    buffer->writeUInt32LE(0x12345678);
    buffer->writeUInt64LE(0x1122334455667788);
    
    buffer->writeInt8(-4);
    buffer->writeInt16LE(-4);
    buffer->writeInt32LE(-4);
    buffer->writeInt64LE(-4);
    
    buffer->writeFloat16LE(100);
    buffer->writeFloatLE(100);
    buffer->writeDoubleLE(100);
    
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

TEST(RingBufferTest, readWrite) {

	RingBuffer* buffer = new RingBuffer(16);

	buffer->writeUInt8(0x12);
	buffer->writeUInt16LE(0x3456);
	buffer->writeUInt32LE(0x12345678);  //7
	buffer->writeUInt64LE(0x1122334455667788); //15

	uint8_t u8= buffer->readUInt8();
	uint16_t u16 = buffer->readUInt16LE();
	uint32_t u32 = buffer->readUInt32LE();

	buffer->writeUInt16LE(0x3456);

	uint64_t u64 = buffer->readUInt64LE();

	u16 = buffer->readUInt16LE();
	EXPECT_EQ(u16, 0x3456);

	buffer->release();
}
