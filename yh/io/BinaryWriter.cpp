#include "BinaryWriter.h"
#include <string>
#include "../base/Internals.h"
#include "IeeeHalfPrecision.h"

NS_YH_IO_BEGIN

BinaryWriter::BinaryWriter(Stream* stream)
	:m_stream(NULL)
{
	setStream(stream);
}

BinaryWriter::~BinaryWriter()
{
	YH_SAFE_RELEASE_NULL(m_stream);
}


//===================== Bytes=========================//
void BinaryWriter::writeBytes(unsigned char* buf, size_t size)
{
	m_stream->writeBytes(buf, size);
}

void BinaryWriter::writeByte(unsigned char value) 
{
	m_stream->writeByte(value);
}

void BinaryWriter::writeUInt8(uint8_t value)
{
	m_stream->writeByte(value);
}

void BinaryWriter::writeInt8(int8_t value)
{
	m_stream->writeByte(value);
}

//=====================LE=========================//

void BinaryWriter::writeUInt16LE(uint16_t value)
{
	unsigned char buf[2] = { 0 };
	buf[0] = value & 0xFF;
	buf[1] = value >> 8;
	writeBytes(buf,2);
}

void BinaryWriter::writeUInt32LE(uint32_t value)
{
	unsigned char buf[4] = { 0 };
	buf[0] = value & 0xFF;
	buf[1] = (value >> 8) & 0xFF;
	buf[2] = (value >> 16) & 0xFF;
	buf[3] = value >> 24;
	writeBytes(buf,4);
}

void BinaryWriter::writeUInt64LE(uint64_t value)
{
	unsigned char buf[8] = { 0 };
	buf[0] = value & 0xFF;
	buf[1] = (value >> 8) & 0xFF;
	buf[2] = (value >> 16) & 0xFF;
	buf[3] = (value >> 24) & 0xFF;
	buf[4] = (value >> 32) & 0xFF;
	buf[5] = (value >> 40) & 0xFF;
	buf[6] = (value >> 48) & 0xFF;
	buf[7] = value >> 56;
	writeBytes(buf, 8);
}

void BinaryWriter::writeInt16LE(int16_t value)
{
	writeUInt16LE(value);
}

void BinaryWriter::writeInt32LE(int32_t value)
{
	writeUInt32LE(value);
}

void BinaryWriter::writeInt64LE(int64_t value)
{
	writeUInt64LE(value);
}

void BinaryWriter::writeHalfFloatLE(float value)
{
	uint16_t halfInt = 0;
	singles2halfp(&halfInt, &value);

	writeUInt16LE(halfInt);
}

void BinaryWriter::writeFloatLE(float value)
{
	unsigned char buf[4];

	floatToByte<float, kLittleEndian>(value, buf);

	writeBytes(buf, 4);
}

void BinaryWriter::writeDoubleLE(double value)
{
	unsigned char buf[8];

	floatToByte<double, kLittleEndian>(value, buf);

	writeBytes( buf, 8);
}

void BinaryWriter::writeHalfFixedLE(float value)
{
	uint16_t fixedInt = (uint16_t)(value * 0x100);

	writeUInt16LE(fixedInt);
}

void BinaryWriter::writeFixedLE(float value)
{
	uint32_t fixedInt = (uint32_t)(value * 0x10000);

	writeUInt32LE(fixedInt);
}

//=====================BE=========================//	

void BinaryWriter::writeUInt16BE(uint16_t value)
{
	unsigned char buf[2] = { 0 };
	buf[1] = value & 0xFF;
	buf[0] = value >> 8;
	writeBytes(buf, 2);
}

void BinaryWriter::writeUInt32BE(uint32_t value)
{
	unsigned char buf[4] = { 0 };
	buf[3] = value & 0xFF;
	buf[2] = (value >> 8) & 0xFF;
	buf[1] = (value >> 16) & 0xFF;
	buf[0] = value >> 24;
	writeBytes(buf, 4);
}

void BinaryWriter::writeUInt64BE(uint64_t value)
{
	unsigned char buf[8] = { 0 };
	buf[7] = value & 0xFF;
	buf[6] = (value >> 8) & 0xFF;
	buf[5] = (value >> 16) & 0xFF;
	buf[4] = (value >> 24) & 0xFF;
	buf[3] = (value >> 32) & 0xFF;
	buf[2] = (value >> 40) & 0xFF;
	buf[1] = (value >> 48) & 0xFF;
	buf[0] = value >> 56;
	writeBytes(buf, 8);
}

void BinaryWriter::writeInt16BE(int16_t value)
{
	writeUInt16BE(value);
}

void BinaryWriter::writeInt32BE(int32_t value)
{
	writeUInt32BE(value);
}

void BinaryWriter::writeInt64BE(int64_t value)
{
	writeUInt64BE(value);
}

void BinaryWriter::writeHalfFloatBE(float value)
{
	uint16_t halfInt = 0;
	singles2halfp(&halfInt, &value);

	return writeUInt16BE(halfInt);
}

void BinaryWriter::writeFloatBE(float value)
{
	unsigned char buf[4];

	floatToByte<float, kBigEndian>(value, buf);

	writeBytes(buf, 4);
}

void BinaryWriter::writeDoubleBE(double value)
{
	unsigned char buf[8];

	floatToByte<double, kBigEndian>(value, buf);

	 writeBytes(buf, 8);
}

void BinaryWriter::writeHalfFixedBE(float value)
{
	uint16_t fixedInt = (uint16_t)(value * 0x100);

	writeUInt16BE(fixedInt);
}

void BinaryWriter::writeFixedBE(float value)
{
	uint32_t fixedInt = (uint32_t)(value * 0x10000);

	writeUInt32BE(fixedInt);
}


void BinaryWriter::seek(size_t legth)
{
	m_stream->seek(legth);
}

bool BinaryWriter::eof()
{
	return m_stream->eof();
}

void BinaryWriter::setStream(Stream* stream)
{
	YH_SAFE_RETAIN(stream);
	YH_SAFE_RELEASE(m_stream);
	m_stream = stream;
}

NS_YH_IO_END
