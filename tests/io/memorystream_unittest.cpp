
#include <stdio.h>
#include <yh/yh.h>
#include <gtest/gtest.h>

USING_NS_YH;
USING_NS_YH_IO;

//test input stream
TEST(MemoryStreamTest, InputStreamLE) {

	unsigned char buf[] = {
		0x12,
		0x56,0x34,
		0x78,0x56,0x34,0x12,
		0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,//15

		0xFC,// signed -4
		0xFC,0xFF,
		0xFC,0xFF,0xFF,0xFF,//22
		0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//30

		0x40,0x56,//float16 100

		0x00,0x00,0xC8,0x42,//float 100

		0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40//double 100
	};


	int bufferSize = sizeof(buf);

	MemoryStream* ms = new MemoryStream(buf, bufferSize);

	BinaryReader* ins = new BinaryReader(ms);

	uint8_t u8 = ins->readUInt8();
	EXPECT_EQ(0x12, u8);

	uint16_t u16 = ins->readUInt16LE();
	EXPECT_EQ(0x3456, u16);

	uint32_t u32 = ins->readUInt32LE();
	EXPECT_EQ(0x12345678, u32);

	uint64_t u64 = ins->readUInt64LE();
	EXPECT_EQ(0x1122334455667788, u64);

	int8_t i8 = ins->readInt8();
	EXPECT_EQ(-4, i8);

	int16_t i16 = ins->readInt16LE();
	EXPECT_EQ(-4, i16);

	int32_t i32 = ins->readInt32LE();
	EXPECT_EQ(-4, i32);

	int64_t i64 = ins->readInt64LE();
	EXPECT_EQ(-4, i64);

	float f16 = ins->readHalfFloatLE();
	EXPECT_EQ(100.0f, f16);

	float f32 = ins->readFloatLE();
	EXPECT_EQ(100.0f, f32);

	double f64 = ins->readDoubleLE();
	EXPECT_EQ(100.0f, f64);

	ins->release();

	ms->release();
}

TEST(MemoryStreamTest, InputStreamBE) {
    
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
    
	MemoryStream* ms=new MemoryStream(buf,bufferSize);

	BinaryReader* ins = new BinaryReader(ms);
    
    uint8_t u8=ins->readUInt8();
    EXPECT_EQ(0x12, u8);
    
    uint16_t u16=ins->readUInt16BE();
    EXPECT_EQ(0x3456, u16);
    
    uint32_t u32=ins->readUInt32BE();
    EXPECT_EQ(0x12345678, u32);
    
    uint64_t u64=ins->readUInt64BE();
    EXPECT_EQ(0x1122334455667788, u64);
    
    int8_t i8=ins->readInt8();
    EXPECT_EQ(-4, i8);
    
    int16_t i16=ins->readInt16BE();
    EXPECT_EQ(-4, i16);
    
    int32_t i32=ins->readInt32BE();
    EXPECT_EQ(-4, i32);
    
    int64_t i64=ins->readInt64BE();
    EXPECT_EQ(-4, i64);
    
    float f16=ins->readHalfFloatBE();
    EXPECT_EQ(100.0f, f16);
    
    float f32=ins->readFloatBE();
    EXPECT_EQ(100.0f, f32);
    
    double f64=ins->readDoubleBE();
    EXPECT_EQ(100.0f, f64);
    
    ins->release();    

	ms->release();
}

TEST(MemoryStreamTest, OutputStreamLE) {

	unsigned char buf[] = {
		0x12,
		0x56,0x34,
		0x78,0x56,0x34,0x12,
		0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11,//15

		0xFC,// signed -4
		0xFC,0xFF,
		0xFC,0xFF,0xFF,0xFF,//22
		0xFC,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,//30

		0x40,0x56,//float16 100

		0x00,0x00,0xC8,0x42,//float 100

		0x00,0x00,0x00,0x00,0x00,0x00,0x59,0x40//double 100
	};
    
    
    int bufferSize=sizeof(buf);
    
	MemoryStream* ms=new MemoryStream(bufferSize);
	BinaryWriter* outs = new BinaryWriter(ms);
    
	outs->writeUInt8(0x12);
	outs->writeUInt16LE(0x3456);
	outs->writeUInt32LE(0x12345678);
	outs->writeUInt64LE(0x1122334455667788);

	outs->writeInt8(-4);
	outs->writeInt16LE(-4);
	outs->writeInt32LE(-4);
	outs->writeInt64LE(-4);

	outs->writeHalfFloatLE(100);
	outs->writeFloatLE(100);
	outs->writeDoubleLE(100);
    
    //check buffer content
    unsigned char* pData=ms->getBuffer();
    
//    for (int i=0; i<bufferSize; ++i) {
//        printf("%x,",*(pData+i));
//    }
//    printf("\n");
    
    for (int i=0; i<bufferSize; ++i) {
        EXPECT_EQ(buf[i], *(pData+i))<<"i="<<i;
    }
    
    outs->release();    

	ms->release();
}


TEST(MemoryStreamTest, OutputStreamBE) {

	unsigned char buf[] = {
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


	int bufferSize = sizeof(buf);

	MemoryStream* ms = new MemoryStream(bufferSize);
	BinaryWriter* outs = new BinaryWriter(ms);

	outs->writeUInt8(0x12);
	outs->writeUInt16BE(0x3456);
	outs->writeUInt32BE(0x12345678);
	outs->writeUInt64BE(0x1122334455667788);

	outs->writeInt8(-4);
	outs->writeInt16BE(-4);
	outs->writeInt32BE(-4);
	outs->writeInt64BE(-4);

	outs->writeHalfFloatBE(100);
	outs->writeFloatBE(100);
	outs->writeDoubleBE(100);

	//check buffer content
	unsigned char* pData = ms->getBuffer();

	//    for (int i=0; i<bufferSize; ++i) {
	//        printf("%x,",*(pData+i));
	//    }
	//    printf("\n");

	for (int i = 0; i < bufferSize; ++i) {
		EXPECT_EQ(buf[i], *(pData + i)) << "i=" << i;
	}

	outs->release();

	ms->release();
}
