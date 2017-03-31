#ifndef YH_IO_BINARYWRITER_H_
#define YH_IO_BINARYWRITER_H_

#include "../YHMacros.h"
#include "../base/Ref.h"
#include "../platform/YHStdC.h"
#include "IOMacros.h"

#include "Stream.h"

NS_YH_IO_BEGIN

/**
 * binary write for stream
 */
class BinaryWriter :public Ref
{
public:
    
	BinaryWriter(Stream* stream);

	~BinaryWriter();

	//===================== Bytes=========================//
	void writeBytes(unsigned char* buf, size_t size);

	 void writeByte(unsigned char value);

	 void writeUInt8(uint8_t value);

	 void writeInt8(int8_t value);
	//=====================LE=========================//

	void writeUInt16LE(uint16_t value);

	void writeUInt32LE(uint32_t value);

	void writeUInt64LE(uint64_t value);

	void writeInt16LE(int16_t value);

	void writeInt32LE(int32_t value);

	void writeInt64LE(int64_t value);

	void writeHalfFloatLE(float value);

	void writeFloatLE(float value);

	void writeDoubleLE(double value);

	void writeHalfFixedLE(float value);

	void writeFixedLE(float value);

	//=====================BE=========================//	

	void writeUInt16BE(uint16_t value);

	void writeUInt32BE(uint32_t value);

	void writeUInt64BE(uint64_t value);

	void writeInt16BE(int16_t value);

	void writeInt32BE(int32_t value);

	void writeInt64BE(int64_t value);

	void writeHalfFloatBE(float value);

	void writeFloatBE(float value);

	void writeDoubleBE(double value);

	void writeHalfFixedBE(float value);

	void writeFixedBE(float value);

	void seek(size_t legth);

	bool eof();

	void setStream(Stream* stream);

protected:
	Stream* m_stream;
};

NS_YH_IO_END

#endif // YH_IO_BINARYWRITER_H_
