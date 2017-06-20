#include "RingBuffer.h"
#include <string>

NS_YH_BEGIN

RingBuffer::RingBuffer()
:m_capacity(0)
,m_data(NULL)
,m_headPosition(0)
,m_tailPosition(0)
{
    
}

RingBuffer::RingBuffer(size_t capacity)
:m_capacity(capacity)
,m_data(NULL)
, m_headPosition(0)
, m_tailPosition(0)
{
    m_data=(unsigned char*) malloc(capacity);
}

RingBuffer::~RingBuffer()
{
    if (m_data) {
        delete m_data;
    }
}

//data和buf不会是重叠内存，所以可以安全使用memcpy
size_t RingBuffer::readBytes(unsigned char* buf,size_t size)
{
	size_t dataSize = getSize();
	size = size>dataSize?dataSize:size;
	if (size > 0)
	{
		//由于size不超过data size,所以不用担心，会超过m_tailPosition.
		if (m_headPosition + size <= m_capacity)
		{
			//直接复制
			memcpy(buf, m_data + m_headPosition, size);
			m_headPosition += size;
		}
		else
		{
			size_t beginSize = m_capacity - m_headPosition;
			size_t  remainSize = size - beginSize;
			memcpy(buf, m_data + m_headPosition, beginSize);
			memcpy(buf + beginSize, m_data, remainSize);
			//m_headPosition回头到读取的位置
			m_headPosition = remainSize;
		}
	}
    
    return size;
}

unsigned char RingBuffer::readByte()
{
	YHASSERT(getSize(), "RingBuffer::readByte out index");
	unsigned char* start = m_data + m_headPosition;
	moveHeadPosition(RING_BUFFER_BYTE_SIZE);
	return *(start);
}

uint8_t RingBuffer::readUInt8()
{
	YHASSERT(getSize(), "RingBuffer::readUInt8 out index");
	unsigned char* start = m_data + m_headPosition;
	moveHeadPosition(RING_BUFFER_BYTE_SIZE);
	return *(start);
}


uint16_t RingBuffer::readUInt16LE()
{
	unsigned char* start = NULL;
	YHASSERT(getSize() >= RING_BUFFER_SHORT_SIZE, "Buffer::readUInt16LE out index");
	if (m_headPosition + RING_BUFFER_SHORT_SIZE <= m_capacity)
	{
		start = m_data + m_headPosition;
		moveHeadPosition(RING_BUFFER_SHORT_SIZE);
		return (*(start + 1) << 8) | *(start);
	}
	else
	{
		//headPostion正好比整个大小小1.
		start = m_data + m_headPosition;
		m_headPosition = 1;
		return (*(m_data) << 8) | *(start);
	}
}

uint16_t RingBuffer::readUInt16BE()
{
	unsigned char* start = NULL;
	YHASSERT(getSize() >= RING_BUFFER_SHORT_SIZE, "Buffer::readUInt16BE out index");
	if (m_headPosition + RING_BUFFER_SHORT_SIZE <= m_capacity)
	{
		start = m_data + m_headPosition;
		moveHeadPosition(RING_BUFFER_SHORT_SIZE);
		return (*(start) << 8) | *(start + 1);
	}
	else
	{
		//headPostion正好比整个大小小1.
		start = m_data + m_headPosition;
		m_headPosition = 1;
		return (*(start) << 8) | *(m_data);
	}
}

uint32_t RingBuffer::readUInt32LE()
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readUInt32LE out index");
	uint32_t val = 0;
	unsigned char* start = m_data + m_headPosition;
	if (m_headPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		val = (uint32_t)*(start + 3) << 24;
		val |= (uint32_t)*(start + 2) << 16;
		val |= (uint32_t)*(start + 1) << 8;
		val |= *(start);
		moveHeadPosition(RING_BUFFER_INT_SIZE);
	}
	else
	{
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			val |= (uint32_t)*(start + i) << (i * 8);
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			val |= (uint32_t)*(m_data + j) << ((j + beginSize) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
	return val;
}

uint32_t  RingBuffer::readUInt32LE2()
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readUInt32LE2 out index");

	unsigned char buf[4];

	readBytes(buf, 4);

	return *((uint32_t*)buf);
}

uint32_t RingBuffer::readUInt32BE()
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readUInt32BE out index");
	
	uint32_t val = 0;
	unsigned char* start = m_data + m_headPosition;
	if (m_headPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		
		val = (uint32_t)*(start) << 24;
		val |= (uint32_t)*(start + 1) << 16;
		val |= (uint32_t)*(start + 2) << 8;
		val |= *(start + 3);
		moveHeadPosition(RING_BUFFER_INT_SIZE);
	}
	else
	{
		size_t shiftSign = RING_BUFFER_INT_SIZE - 1;
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			val |= (uint32_t)*(start + i) << (( shiftSign - i) * 8);
		}
		 shiftSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			val |= (uint32_t)*(m_data + j) << (( shiftSign - j) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
	return val;
}

uint64_t RingBuffer::readUInt64LE()
{
    YHASSERT(getSize()>=RING_BUFFER_LONG_SIZE,"RingBuffer::readUInt64LE out 64 index");
	uint64_t val = 0;
	unsigned char* start = m_data + m_headPosition;

	if (m_headPosition + RING_BUFFER_LONG_SIZE <= m_capacity)
	{
		for (unsigned int i = 0; i <RING_BUFFER_LONG_SIZE; i++)
		{
			val |= (uint64_t)*(start + i) << (i * 8);
		}
		moveHeadPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start+i) << (i * 8);
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			val |= (uint64_t)*(m_data + j) << ( (j+beginSize) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
    return val;
}

uint64_t RingBuffer::readUInt64BE()
{
    YHASSERT(getSize() >= RING_BUFFER_LONG_SIZE,"RingBuffer::readUInt64BE out index");
	uint64_t val = 0;
	if (m_headPosition + RING_BUFFER_LONG_SIZE <= m_capacity)
	{
		unsigned char* start = m_data + m_headPosition + RING_BUFFER_LONG_SIZE-1;

		for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
		{
			val |= (uint64_t) *(start--) << (i * 8);
		}
		moveHeadPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		unsigned char* start = m_data + m_headPosition;
		size_t shiftSign = RING_BUFFER_LONG_SIZE - 1;
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start + i) << (( shiftSign-i) * 8);
		}
		 shiftSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;			
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			val |= (uint64_t)*(m_data + j) << (( shiftSign-j) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
    return val;
}

float  RingBuffer::readFloat16LE()
{
	YHASSERT(getSize() >= RING_BUFFER_SHORT_SIZE, "Buffer::readFloat16LE out index");

	uint16_t halfInt = readUInt16LE();

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

float RingBuffer::readFloat16BE()
{
	YHASSERT(getSize() >= RING_BUFFER_SHORT_SIZE, "Buffer::readFloat16BE out index");
	//        uint16_t halfInt=readUInt16BE(position);
	//        
	//        uint32_t singleInt=0;
	//        
	//        //半精度转单精度
	//        halfp2singlesTyped(&singleInt, &halfInt);
	//                
	//        return bitwise_cast<uint32_t,float>(singleInt);

	uint16_t halfInt = readUInt16BE();

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

float RingBuffer::readFloatLE()
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readFloatLE out index");
	unsigned char floatBuffer[4];
	readBytes(floatBuffer, 4);
	return byteToFloat<float, kLittleEndian>(floatBuffer);
}

float RingBuffer::readFloatBE()
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readFloatBE out index");
	unsigned char floatBuffer[4];
	readBytes(floatBuffer,4);
	return byteToFloat<float, kBigEndian>(floatBuffer);
}

double RingBuffer::readDoubleLE()
{
	YHASSERT(getSize() >= RING_BUFFER_LONG_SIZE, "Buffer::readDoubleLE out index");
	unsigned char floatBuffer[8];
	readBytes(floatBuffer, 8);
	return byteToFloat<double, kLittleEndian>(floatBuffer);
}

double RingBuffer::readDoubleBE()
{
	YHASSERT(getSize() >= RING_BUFFER_LONG_SIZE, "Buffer::readDoubleBE out index");
	unsigned char floatBuffer[8];
	readBytes(floatBuffer, 8);
	return byteToFloat<double, kBigEndian>(floatBuffer);
}

size_t RingBuffer::writeBytes(unsigned char* buf,size_t size)
{
	size_t dataSize = getEmptySize();

	size_t writeSize = MIN(dataSize, size);

	if (writeSize > 0)
	{
		if (m_tailPosition + writeSize <= m_capacity)
		{
			//未到达数据结束位置，直接copy
			memcpy(m_data + m_tailPosition, buf, writeSize);
			m_tailPosition += writeSize;
		}
		else
		{
			//数据被分割
			size_t beginSize = m_capacity - m_tailPosition;
			memcpy(m_data + m_tailPosition,buf,beginSize);
			size_t remainSize = writeSize - beginSize;
			memcpy(m_data, buf + beginSize,remainSize);
			m_tailPosition = remainSize;
		}
	}
    return writeSize;
}

size_t RingBuffer::writeByte(unsigned char value)
{
	YHASSERT(getEmptySize() >= RING_BUFFER_BYTE_SIZE, "Buffer::writeByte out index");

	*(m_data + m_tailPosition) = value;
	moveTailPosition(RING_BUFFER_BYTE_SIZE);
	return RING_BUFFER_BYTE_SIZE;
}

size_t RingBuffer::writeUInt8(uint8_t value)
{
	YHASSERT(getEmptySize() >= RING_BUFFER_BYTE_SIZE, "Buffer::writeUInt8 out index");

	*(m_data + m_tailPosition) = value;
	moveTailPosition(RING_BUFFER_BYTE_SIZE);
	return RING_BUFFER_BYTE_SIZE;
}

size_t RingBuffer::writeUInt16LE(uint16_t value)
{
	YHASSERT(getEmptySize() >= RING_BUFFER_SHORT_SIZE, "Buffer::writeUInt16LE out index");

	unsigned char* start = m_data + m_tailPosition;

	*(start) = value & 0x00FF;
	if (m_tailPosition + RING_BUFFER_SHORT_SIZE <= m_capacity)
	{
		*(start + 1) = (value & 0xFF00) >> 8;
		moveTailPosition(RING_BUFFER_SHORT_SIZE);
	}
	else
	{
		*(m_data) = (value & 0xFF00) >> 8;
		m_tailPosition = 1;
	}

	return RING_BUFFER_SHORT_SIZE;
}

size_t RingBuffer::writeUInt16BE(uint16_t value)
{
	YHASSERT(getEmptySize() >= RING_BUFFER_SHORT_SIZE, "Buffer::writeUInt16BE out index");

	unsigned char* start = m_data + m_tailPosition;

	*(start) = (value & 0xFF00) >> 8;;
	if (m_tailPosition + RING_BUFFER_SHORT_SIZE <= m_capacity)
	{
		*(start + 1) = value & 0x00FF;
		moveTailPosition(RING_BUFFER_SHORT_SIZE);
	}
	else
	{
		*(m_data) = value & 0x00FF;
		m_tailPosition = 1;
	}

	return RING_BUFFER_SHORT_SIZE;
}

size_t RingBuffer::writeUInt32LE(uint32_t value)
{
	YHASSERT(getEmptySize() > RING_BUFFER_INT_SIZE, "Buffer::writeUInt32LE out index");

	unsigned char* start = m_data + m_tailPosition;

	if (m_tailPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		*(start) = value & 0xFF;
		*(start + 1) = (value >> 8) & 0xFF;
		*(start + 2) = (value >> 16) & 0xFF;
		*(start + 3) = (value >> 24) & 0xFF;
		moveTailPosition(RING_BUFFER_INT_SIZE);
	}
	else
	{
		//处理尾位置到数据结束的数据
		size_t beginSize = m_capacity - m_tailPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			*(start + i) = (value >> (i * 8)) & 0xFF;
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			*(m_data + j) = (value >> ((j + beginSize) * 8)) & 0xFF;
		}
		//此时头位置开好是剩余数据的大小
		m_tailPosition = remainSize;
	}

	return RING_BUFFER_INT_SIZE;
}

size_t RingBuffer::writeUInt32BE(uint32_t value)
{
	YHASSERT(getEmptySize() > RING_BUFFER_INT_SIZE, "Buffer::writeUInt32BE out index");

	unsigned char* start = m_data + m_tailPosition;

	if (m_tailPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		*(start) = (value >> 24) & 0xFF;
		*(start + 1) = (value >> 16) & 0xFF;
		*(start + 2) = (value >> 8) & 0xFF;
		*(start + 3) = value & 0xFF;
		moveTailPosition(RING_BUFFER_INT_SIZE);
	}
	else
	{
		size_t shiftSign = RING_BUFFER_INT_SIZE - 1;
		//处理尾位置到数据结束的数据
		size_t beginSize = m_capacity - m_tailPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			*(start + i) = (value >> ((shiftSign - i) * 8)) & 0xFF;
		}
		shiftSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			*(m_data + j) = (value >> (shiftSign - j) * 8) & 0xFF;
		}
		//此时头位置开好是剩余数据的大小
		m_tailPosition = remainSize;
	}
	return RING_BUFFER_INT_SIZE;
}

size_t RingBuffer::writeUInt64LE(uint64_t value)
{
    YHASSERT(getEmptySize()>RING_BUFFER_LONG_SIZE,"RingBuffer::writeUInt64LE out index");
    
    unsigned char* start=m_data+m_tailPosition;

	if (m_tailPosition + RING_BUFFER_LONG_SIZE <= m_capacity)
	{
		for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
		{
			*(start + i) = (value >> (i * 8)) & 0xFF;
		}
		moveTailPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		//处理尾位置到数据结束的数据
		size_t beginSize = m_capacity - m_tailPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			*(start + i) = (value >> (i * 8)) & 0xFF;
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			*(m_data + j) = (value >> ((j + beginSize) * 8)) & 0xFF;
		}
		//此时头位置开好是剩余数据的大小
		m_tailPosition = remainSize;
	}    
    
    return RING_BUFFER_LONG_SIZE;
}

size_t RingBuffer::writeUInt64BE(uint64_t value)
{
    YHASSERT(getEmptySize()>RING_BUFFER_LONG_SIZE,"RingBuffer::writeUInt64LE out index");
    
	if (m_tailPosition + RING_BUFFER_LONG_SIZE <= m_capacity)
	{
		unsigned char* start = m_data + m_tailPosition + RING_BUFFER_LONG_SIZE-1;

		for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
		{
			*(start--) = (value >> (i * 8)) & 0xFF;
		}
		moveTailPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		size_t shiftSign = RING_BUFFER_LONG_SIZE - 1;
		unsigned char* start = m_data + m_tailPosition;

		//处理尾位置到数据结束的数据
		size_t beginSize = m_capacity - m_tailPosition;
		for (unsigned int i = 0; i < beginSize; ++i)
		{
			*(start + i) = (value >> (( shiftSign - i) * 8)) & 0xFF;
		}
		 shiftSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;
		for (unsigned int j = 0; j < remainSize; ++j)
		{
			*(m_data + j) = (value >> ( shiftSign - j) * 8) & 0xFF;
		}
		//此时头位置开好是剩余数据的大小
		m_tailPosition = remainSize;
	}

    
    return RING_BUFFER_LONG_SIZE;
}

void RingBuffer::fill(unsigned char value,size_t start,size_t end)
{
	size_t startInBuffer = m_headPosition + start;
	size_t fillSize = end - start;

	if (startInBuffer < m_capacity)
	{
		size_t firstSize = m_capacity - startInBuffer;
		memset(m_data + startInBuffer, value, firstSize);

		size_t remainSize = fillSize - firstSize;

		if (remainSize > 0)
		{
			//从data开始处进行填充
			memset(m_data, value, remainSize);
		}
	}
}

void RingBuffer::copy(RingBuffer* target,size_t sourceStart,size_t sourceEnd)
{
    if (sourceStart >= sourceEnd){
        //do nothing
        return;
    }
	
	size_t targetLength = target->getSize();

	if (sourceStart > getSize()) {
		YHINFO("RingBuffer::copy out of range index");
		return;
	}
    
    //检查目录缓存区大小是否可以容纳，不能则截取
    if (sourceEnd - sourceStart > targetLength)
        sourceEnd = sourceStart + targetLength;
    
    size_t to_copy = MIN(sourceEnd - sourceStart,getSize() - sourceStart);
    
	if (m_headPosition + sourceStart < m_capacity)
	{
		memmove(target->getWriter(), m_data+ m_headPosition + sourceStart, to_copy);
	}
	else
	{
		size_t beginSize = m_capacity - (m_headPosition + sourceStart);
		size_t remainSize = to_copy - beginSize;

		memmove(target->getWriter(), m_data + m_headPosition + sourceStart, to_copy);
	}

    
}

size_t RingBuffer::getSize()
{
	if (m_headPosition == m_tailPosition)
	{
		return 0;
	}
	else	if (m_tailPosition > m_headPosition)
	{
		return m_tailPosition - m_headPosition;
	}
	else
	{
		return m_capacity - m_headPosition + m_tailPosition;
	}
}

size_t RingBuffer::getEmptySize()
{
	size_t size = 0;
	if (m_tailPosition >= m_headPosition)
	{
		size = m_capacity - m_tailPosition+m_headPosition;
	}
	else
	{
		size = m_headPosition - m_tailPosition;
	}
	return size;
}

NS_YH_END
