#ifndef YH_IO_BUFFERREADER_H_
#define YH_IO_BUFFERREADER_H_

#include "../YHMacros.h"
#include "../base/Ref.h"
#include "../platform/YHStdC.h"
#include "IOMacros.h"

#include "Stream.h"

NS_YH_IO_BEGIN

/**
 * binary reader for stream
 */
class BinaryReader:public Ref
{
public:
    
    BinaryReader(Stream* stream);

    ~BinaryReader();
    
	//===================== Bytes=========================//
	size_t readBytes(unsigned char* buf,size_t size);
    
    unsigned char readByte();

	uint8_t readUInt8();

	int8_t readInt8();
	//=====================LE=========================//

    uint16_t readUInt16LE();
    
    uint32_t readUInt32LE();
    
    uint64_t readUInt64LE();   
	    
    int16_t readInt16LE();
    
    int32_t readInt32LE();
    
    int64_t readInt64LE();
    
    float readHalfFloatLE();
    
    float readFloatLE();
    
    double readDoubleLE();
    
    float readHalfFixedLE();
    
    float readFixedLE();

	//=====================BE=========================//	

	uint16_t readUInt16BE();

	uint32_t readUInt32BE();

	uint64_t readUInt64BE();

	int16_t readInt16BE();

	int32_t readInt32BE();

	int64_t readInt64BE();

	float readHalfFloatBE();

	float readFloatBE();

	double readDoubleBE();

	float readHalfFixedBE();

	float readFixedBE();
    
    void seek(size_t legth);

    bool eof();

	void setStream(Stream* stream);

protected:
	Stream* m_stream;
};

NS_YH_IO_END

#endif // YH_IO_BUFFERREADER_H_
