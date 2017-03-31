#include "Buffer.h"
#include <string>

NS_YH_IO_BEGIN

Buffer::Buffer()
:m_size(0)
,m_data(NULL)
,m_dataOwner(false)
{
    
}

Buffer::Buffer(size_t size)
:m_size(size)
,m_data(NULL)
,m_dataOwner(true)
{
    m_data=(unsigned char*) malloc( size);
}

Buffer::Buffer(unsigned char* data,size_t size)
:m_size(size)
,m_data(data)
,m_dataOwner(false)
{
    
}

Buffer::Buffer(unsigned char* data,size_t size,bool dataOwner)
:m_size(size)
,m_dataOwner(dataOwner)
{
	if (dataOwner) 
	{
		m_data = (unsigned char*)malloc(size);
		memcpy(m_data, data, size);
	}
	else
	{
		m_data = data;
	}
}

Buffer::~Buffer()
{
    if (m_data && m_dataOwner) {
        free(m_data);
    }
}

size_t Buffer::readBytes(size_t position, unsigned char* buf,size_t size)
{
    YHASSERT(position<m_size,"Buffer::readBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    //通常buf和m_data不在同一内存块内，可以使用memcpy
	memcpy(buf,m_data+position,size);
    
    return size;
}

size_t Buffer::readBytesSafe(size_t position, void* buf, size_t size)
{
	YHASSERT(position + size <= m_size, "Buffer::readBytesSafe out index");

	if (position + size > m_size) {
		size = m_size - position;
	}

	memmove(buf, m_data + position, size);

	return size;
}

uint64_t Buffer::readUInt64LE(size_t position)
{
    YHASSERT(position+8<=m_size,"Buffer::readUInt64LE out 64 index");

    unsigned char* start=m_data+position;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t)*(start+i) << (i*8);
    }

    return val;
}

uint32_t Buffer::readUInt32LE(size_t position)
{
	YHASSERT(position + YH_IO_INT_SIZE <= m_size, "Buffer::readUInt32LE out index");

	unsigned char* start = m_data + position;

	uint32_t val = (uint32_t)*(start + 3) << 24;
	val |= (uint32_t)*(start + 2) << 16;
	val |= (uint32_t)*(start + 1) << 8;
	val |= *(start);

	return val;
}

//使用字节转换来读取数据，比直接计算要慢20%左右。性能估计还是消耗在memcpy上。
//所以还是直接使用数值运算快
//uint32_t Buffer::readUInt32LE2(size_t position)
//{
//	YHASSERT(position + YH_IO_INT_SIZE <= m_size, "Buffer::readUInt32BE out index");
//
//	unsigned char buf[4];
//
//	readBytes(position, buf, 4);
//
//	return *((uint32_t*)buf);
//}

uint32_t Buffer::readUInt32BE(size_t position)
{
	YHASSERT(position + YH_IO_INT_SIZE <= m_size, "Buffer::readUInt32BE out index");

	unsigned char* start = m_data + position;

	uint32_t val = (uint32_t)*(start) << 24;
	val |= (uint32_t)*(start + 1) << 16;
	val |= (uint32_t)*(start + 2) << 8;
	val |= *(start + 3);

	return val;
}

uint64_t Buffer::readUInt64BE(size_t position)
{
    YHASSERT(position+8<=m_size,"Buffer::readUInt64BE out index");
                
    unsigned char* start=m_data+position+7;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t) *(start--) << (i*8);
    }

    return val;
}

float Buffer::readFloat16LE(size_t position)
{
	YHASSERT(position + YH_IO_SHORT_SIZE <= m_size, "Buffer::readFloat16LE out index");
	//        uint16_t halfInt=readUInt16LE(position);
	//        
	//        uint32_t singleInt=0;
	//        
	//        //半精度转单精度
	//        halfp2singlesTyped(&singleInt, &halfInt);
	//        
	//        return bitwise_cast<uint32_t,float>(singleInt);

	uint16_t halfInt = readUInt16LE(position);

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

float Buffer::readFloat16BE(size_t position)
{
	YHASSERT(position + YH_IO_SHORT_SIZE <= m_size, "Buffer::readFloat16BE out index");
	//        uint16_t halfInt=readUInt16BE(position);
	//        
	//        uint32_t singleInt=0;
	//        
	//        //半精度转单精度
	//        halfp2singlesTyped(&singleInt, &halfInt);
	//                
	//        return bitwise_cast<uint32_t,float>(singleInt);

	uint16_t halfInt = readUInt16BE(position);

	float val;

	//半精度转单精度
	halfp2singles(&val, &halfInt);

	return val;
}

size_t Buffer::writeBytes(size_t position, unsigned char* buf,size_t size)
{
    YHASSERT(position<m_size,"Buffer::writeBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
	memcpy(m_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeBytesSafe(size_t position, unsigned char* buf,size_t size)
{
    YHASSERT(position+size<=m_size,"Buffer::writeBytes out index");
    
	if (position + size > m_size) {
		size = m_size - position;
	}
    
	memmove(m_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeUInt16LE(uint16_t value, size_t position)
{
	YHASSERT(position + YH_IO_SHORT_SIZE <= m_size, "Buffer::writeUInt16LE out index");

	unsigned char* start = m_data + position;

	*(start) = value & 0x00FF;
	*(start + 1) = (value & 0xFF00) >> 8;

	return YH_IO_SHORT_SIZE;
}

size_t  Buffer::writeUInt16BE(uint16_t value, size_t position)
{
	YHASSERT(position + YH_IO_SHORT_SIZE <= m_size, "Buffer::writeUInt16BE out index");

	unsigned char* start = m_data + position;

	*(start) = (value & 0xFF00) >> 8;
	*(start + 1) = value & 0x00FF;

	return YH_IO_SHORT_SIZE;
}

size_t Buffer::writeUInt32LE(uint32_t value, size_t position)
{
	YHASSERT(position + YH_IO_INT_SIZE <= m_size, "Buffer::writeUInt32LE out index");

	unsigned char* start = m_data + position;

	*(start) = value & 0xFF;
	*(start + 1) = (value >> 8) & 0xFF;
	*(start + 2) = (value >> 16) & 0xFF;
	*(start + 3) = (value >> 24) & 0xFF;

	return YH_IO_INT_SIZE;
}

size_t Buffer::writeUInt32BE(uint32_t value, size_t position)
{
	YHASSERT(position + YH_IO_INT_SIZE <= m_size, "Buffer::writeUInt32BE out index");

	unsigned char* start = m_data + position;

	*(start) = (value >> 24) & 0xFF;
	*(start + 1) = (value >> 16) & 0xFF;
	*(start + 2) = (value >> 8) & 0xFF;
	*(start + 3) = value & 0xFF;

	return YH_IO_INT_SIZE;
}

size_t Buffer::writeUInt64LE(uint64_t value,size_t position)
{
    YHASSERT(position+YH_IO_LONG_SIZE<=m_size,"Buffer::writeUInt64LE out index");
    
    
    unsigned char* start=m_data+position;
    
    for (int i = 0; i < YH_IO_LONG_SIZE; i++)
    {
        *(start+i) =  (value >> (i*8)) & 0xFF;
    }
    
    return YH_IO_LONG_SIZE;
}

size_t Buffer::writeUInt64BE(uint64_t value,size_t position)
{
    YHASSERT(position+YH_IO_LONG_SIZE<=m_size,"Buffer::writeUInt64LE out index");
    
    unsigned char* start=m_data+position+7;
    
    for (int i = 0; i < YH_IO_LONG_SIZE; i++)
    {
        *(start--) =  (value >> (i*8)) & 0xFF;
    }
    
    return YH_IO_LONG_SIZE;
}

void Buffer::fill(unsigned char value,size_t start,size_t end)
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

void Buffer::copy(Buffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd)
{
    size_t targetLength=target->getSize();
    
    if (targetStart >= target->getSize() || sourceStart >= sourceEnd){
        //do nothing
        return;
    }
    
    if (sourceStart > m_size){
        YHINFO("Buffer::copy out of range index");
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

unsigned char* Buffer::slice(size_t start,size_t* size)
{
    YHASSERT(start<m_size, "Buffer::slice out of range index");
    
    if (start+(*size)>m_size) {
        *size=m_size-start;
    }
    
    return m_data+start;
}

void Buffer::setData(unsigned char* data, size_t size,bool dataOwner)
{
	//remove old data
	if (m_data && m_dataOwner)
	{
		delete m_data;
	}

	//set new data
	m_dataOwner = dataOwner;
	m_size = size;

	if (size > 0)
	{
		if (dataOwner)
		{
			m_data = (unsigned char*)malloc(size);
			memcpy(m_data, data, size);
		}
		else
		{
			m_data = data;
		}
	}
	else
	{
		m_data = NULL;
	}
}

NS_YH_IO_END
