#include "BinaryReader.h"
#include <string>
#include "../platform/Internals.h"
#include "IeeeHalfPrecision.h"

NS_YH_IO_BEGIN
BinaryReader::BinaryReader(Stream* stream)
	:m_stream(NULL)
{
	setStream(stream);
}

BinaryReader::~BinaryReader()
{
	YH_SAFE_RELEASE_NULL(m_stream);
}

size_t BinaryReader::readBytes(unsigned char* buf, size_t size)
{
	return m_stream->readBytes(buf,size);
}

unsigned char BinaryReader::readByte()
{
	return m_stream->readByte();
}

uint8_t BinaryReader::readUInt8()
{
	return (uint8_t)m_stream->readByte();
}

int8_t BinaryReader::readInt8()
{
	return (int8_t)m_stream->readByte();
}


//=====================LE=========================//

uint16_t BinaryReader::readUInt16LE()
{
	unsigned char buf[2] = { 0 };
	readBytes(buf,2);
	return buf[0] | (uint16_t)buf[1] << 8;
}

uint32_t BinaryReader::readUInt32LE()
{
	unsigned char buf[4] = { 0 };
	readBytes(buf, 4);
	return buf[0] | (uint32_t)buf[1] << 8 | (uint32_t)buf[2] <<16 | (uint32_t)buf[3]<<24;
}

uint64_t BinaryReader::readUInt64LE()
{
	unsigned char buf[8] = { 0 };
	readBytes(buf, 8);
	return buf[0] | (uint64_t)buf[1] << 8 | (uint64_t)buf[2] << 16 | (uint64_t)buf[3] << 24
		| (uint64_t)buf[4] <<32 | (uint64_t)buf[5] << 40 | (uint64_t)buf[6] << 48 | (uint64_t)buf[7] << 56;
}

int16_t BinaryReader::readInt16LE()
{
	return (int16_t)readUInt16LE();
}

int32_t BinaryReader::readInt32LE() 
{
	return (int32_t)readUInt32LE();
}

int64_t BinaryReader::readInt64LE()
{
	return (int64_t)readUInt64LE();
}

float BinaryReader::readHalfFloatLE()
{
	uint16_t halfInt = readUInt16LE();

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

float BinaryReader::readFloatLE()
{
	unsigned char buf[4] = { 0 };
	readBytes(buf, 4);
	return byteToFloat<float, kLittleEndian>(buf);
}

double BinaryReader::readDoubleLE()
{
	unsigned char buf[8] = { 0 };
	readBytes(buf, 8);
	return byteToFloat<double, kLittleEndian>(buf);
}

float BinaryReader::readHalfFixedLE()
{
	return (float)readUInt16LE() / 0x100;
}

float BinaryReader::readFixedLE()
{
	return (float)readUInt32LE() / 0x10000;
}

//=====================BE=========================//	

uint16_t BinaryReader::readUInt16BE()
{
	unsigned char buf[2] = { 0 };
	readBytes(buf, 2);
	return (uint16_t)buf[0] << 8 | buf[1];
}

uint32_t BinaryReader::readUInt32BE()
{
	unsigned char buf[4] = { 0 };
	readBytes(buf, 4);
	return buf[3] | (uint32_t)buf[2] << 8 | (uint32_t)buf[1] << 16 | (uint32_t)buf[0] << 24;
}

uint64_t BinaryReader::readUInt64BE()
{
	unsigned char buf[8] = { 0 };
	readBytes(buf, 8);
	return buf[7] | (uint64_t)buf[6] << 8 | (uint64_t)buf[5] << 16 | (uint64_t)buf[4] << 24
		| (uint64_t)buf[3] << 32 | (uint64_t)buf[2] << 40 | (uint64_t)buf[1] << 48 | (uint64_t)buf[0] << 56;
}

int16_t BinaryReader::readInt16BE()
{
	return (int16_t)readUInt16BE();
}

int32_t BinaryReader::readInt32BE()
{
	return (int32_t)readUInt32BE();
}

int64_t BinaryReader::readInt64BE()
{
	return (int64_t)readUInt64BE();
}

float BinaryReader::readHalfFloatBE()
{
	uint16_t halfInt = readUInt16BE();

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

float BinaryReader::readFloatBE()
{
	unsigned char buf[4] = { 0 };
	readBytes(buf, 4);
	return byteToFloat<float, kBigEndian>(buf);
}

double BinaryReader::readDoubleBE()
{
	unsigned char buf[8] = { 0 };
	readBytes(buf, 8);
	return byteToFloat<double, kBigEndian>(buf);
}

float BinaryReader::readHalfFixedBE()
{
	return (float)readUInt16BE() / 0x100;
}

float BinaryReader::readFixedBE()
{
	return (float)readUInt32BE() / 0x10000;
}


void BinaryReader::seek(size_t legth)
{
	m_stream->seek(legth);
}

bool BinaryReader::eof()
{
	return m_stream->eof	();
}

void BinaryReader::setStream(Stream* stream)
{
	YH_SAFE_RETAIN(stream);
	YH_SAFE_RELEASE(m_stream);
	m_stream = stream;
}
NS_YH_IO_END
