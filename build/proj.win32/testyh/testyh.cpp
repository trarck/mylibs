// testyh.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <yh/yh.h>

USING_NS_YH;

int _tmain(int argc, _TCHAR* argv[])
{
    YHDEBUG("hello world");

    
	Buffer* buffer=new Buffer(12);

    unsigned char buf[12]={
        0x01,0x02,0x03,0x04,
        0x05,0x06,0x07,0x08,
        0x09,0x0A,0x0B,0x0C
    };

    buffer->writeBytes(0,buf,100);


    uint8_t u8=buffer->readUInt8(0);
    YHDEBUG("u8=%x",u8);

    uint16_t u16le=buffer->readUInt16LE(1);
    YHDEBUG("u16le=%04x",u16le);

    uint16_t u16be=buffer->readUInt16BE(1);
    YHDEBUG("u16le=%04x",u16be);

    uint32_t u32le=buffer->readUInt32LE(2);
    YHDEBUG("u32le=%08x",u32le);

    uint32_t u32be=buffer->readUInt32BE(2);
    YHDEBUG("u32be=%08x",u32be);

    uint64_t u64le=buffer->readUInt64LE(3);
    YHDEBUG("u64le=%016llx",u64le);

    uint64_t u64be=buffer->readUInt64BE(4);
    YHDEBUG("u64be=%016llx",u64be);

    buffer->release();
    
    getchar();
    return 0;
}

