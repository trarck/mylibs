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
size_t RingBuffer::readBytes(void* buf,size_t size)
{
	size_t dataSize = getSize();
	size = size>dataSize?dataSize:size;
	if (size > 0)
	{
		if (m_tailPosition > m_headPosition)
		{
			memcpy(buf, m_data + m_headPosition, size);
			//这里m_headPosition一定小于m_capacity,可以安全加上size.
			m_headPosition += size;
		}
		else
		{
			size_t beginSize = m_capacity - m_headPosition;
			if (beginSize > size)
			{
				memcpy(buf, m_data + m_headPosition, size);
				//这里m_headPosition一定小于m_capacity,可以安全加上size.
				m_headPosition += size;
			}
			else
			{
				size_t  remainSize = size - beginSize;
				memcpy(buf, m_data + m_headPosition, beginSize);
				memcpy(buf+ beginSize, m_data, remainSize);
				//m_headPosition回头到读取的位置
				m_headPosition = remainSize;
			}	
		}
	}
    
    return size;
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
	if (m_headPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		unsigned char* start = m_data + m_headPosition;
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
		for (int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start + i) << (i * 8);
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (int j = 0; j < remainSize; ++j)
		{
			val |= (uint64_t)*(m_data + j) << ((j + beginSize) * 8);
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

uint32_t RingBuffer::readUInt32BE(size_t position)
{
	YHASSERT(getSize() >= RING_BUFFER_INT_SIZE, "Buffer::readUInt32BE out index");
	
	uint32_t val = 0;

	if (m_headPosition + RING_BUFFER_INT_SIZE <= m_capacity)
	{
		unsigned char* start = m_data + m_headPosition;
		val = (uint32_t)*(start) << 24;
		val |= (uint32_t)*(start + 1) << 16;
		val |= (uint32_t)*(start + 2) << 8;
		val |= *(start + 3);
		moveHeadPosition(RING_BUFFER_INT_SIZE);
	}
	else
	{
		unsigned char* start = m_data + position;
		short MoveSign = RING_BUFFER_INT_SIZE - 1;
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start + i) << ((MoveSign - i) * 8);
		}
		MoveSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_INT_SIZE - beginSize;
		for (int j = 0; j < remainSize; ++j)
		{
			val |= (uint64_t)*(m_data + j) << ((MoveSign - j) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
	return val;
}

uint64_t RingBuffer::readUInt64LE()
{
    YHASSERT(getSize()>=RING_BUFFER_LONG_SIZE <,"RingBuffer::readUInt64LE out 64 index");
	uint64_t val = 0;
	unsigned char* start = m_data + m_headPosition;

	if (m_headPosition + RING_BUFFER_LONG_SIZE <= m_capacity)
	{
		for (int i = 0; i <RING_BUFFER_LONG_SIZE; i++)
		{
			val |= (uint64_t)*(start + i) << (i * 8);
		}
		moveHeadPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start+i) << (i * 8);
		}
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;
		for (int j = 0; j < remainSize; ++j)
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

		uint64_t val = 0;

		for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
		{
			val |= (uint64_t) *(start--) << (i * 8);
		}
		moveHeadPosition(RING_BUFFER_LONG_SIZE);
	}
	else
	{
		unsigned char* start = m_data + m_headPosition;
		short MoveSign = RING_BUFFER_LONG_SIZE - 1;
		//处理头位置到数据结束的数据
		size_t beginSize = m_capacity - m_headPosition;
		for (int i = 0; i < beginSize; ++i)
		{
			val |= (uint64_t)*(start + i) << ((MoveSign-i) * 8);
		}
		MoveSign -= beginSize;
		//处理剩余数据，此时是环的开始位置
		size_t remainSize = RING_BUFFER_LONG_SIZE - beginSize;			
		for (int j = 0; j < remainSize; ++j)
		{
			val |= (uint64_t)*(m_data + j) << ((MoveSign-j) * 8);
		}
		//此时头位置开好是剩余数据的大小
		m_headPosition = remainSize;
	}
    return val;
}

size_t RingBuffer::writeBytes(size_t position,void* buf,size_t size)
{
    YHASSERT(position<m_size,"RingBuffer::writeBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(m_data+position,buf,size);
    
    return size;
}

size_t RingBuffer::writeBytesUnSafe(size_t position,void* buf,size_t size)
{
    YHASSERT(position+size<=m_size,"RingBuffer::writeBytes out index");
    
//    if (position+size>m_size) {
//        size=m_size-position;
//    }
    
    memcpy(m_data+position,buf,size);
    
    return size;
}

size_t RingBuffer::writeUInt64LE(uint64_t value,size_t position)
{
    YHASSERT(position+RING_BUFFER_LONG_SIZE<=m_size,"RingBuffer::writeUInt64LE out index");
    
    
    unsigned char* start=m_data+position;
    
    for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
    {
        *(start+i) =  (value >> (i*8)) & 0xFF;
    }
    
    return RING_BUFFER_LONG_SIZE;
}

size_t RingBuffer::writeUInt64BE(uint64_t value,size_t position)
{
    YHASSERT(position+RING_BUFFER_LONG_SIZE<=m_size,"RingBuffer::writeUInt64LE out index");
    
    unsigned char* start=m_data+position+7;
    
    for (int i = 0; i < RING_BUFFER_LONG_SIZE; i++)
    {
        *(start--) =  (value >> (i*8)) & 0xFF;
    }
    
    return RING_BUFFER_LONG_SIZE;
}

void RingBuffer::fill(unsigned char value,size_t start,size_t end)
{
    if (start<m_size) {
        
        if (end>m_size) {
            end=m_size;
        }
        
        size_t len=end-start;
        
        if (len>0) {
            memset(m_data+start, value, len);
        }
    }
}

void RingBuffer::copy(RingBuffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd)
{
    size_t targetLength=target->getSize();
    
    if (targetStart >= target->getSize() || sourceStart >= sourceEnd){
        //do nothing
        return;
    }
    
    if (sourceStart > m_size){
        YHINFO("RingBuffer::copy out of range index");
        return;
    }
    
    //检查目录缓存区大小是否可以容纳，不能则截取
    if (sourceEnd - sourceStart > targetLength - targetStart)
        sourceEnd = sourceStart + targetLength - targetStart;
    
    size_t to_copy = MIN(MIN(sourceEnd - sourceStart,
                               targetLength - targetStart),
                           m_size - sourceStart);
    
    memmove(target->getData()+targetStart, m_data+sourceStart, to_copy);
}

unsigned char* RingBuffer::slice(size_t start,size_t* size)
{
    YHASSERT(start<m_size, "RingBuffer::slice out of range index");
    
    if (start+(*size)>m_size) {
        *size=m_size-start;
    }
    
    return m_data+start;
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

NS_YH_END
