#include "MemoryStream.h"
#include <string>

NS_YH_IO_BEGIN

MemoryStream::MemoryStream()
:m_length(0)
,m_buffer(nullptr)
{
    
}

MemoryStream::MemoryStream(size_t capacity)
	:m_capacity(capacity)
	,m_length(0)
{
	m_buffer = (unsigned char*)malloc(capacity);
}


MemoryStream::MemoryStream(unsigned char* data, size_t size)
	:m_capacity(size)
	,m_length(size)
{
	m_buffer = (unsigned char*)malloc(size);
	if (m_buffer != nullptr && data!=nullptr) {
		memcpy(m_buffer, data, size);
	}
}

MemoryStream::~MemoryStream()
{
	if(m_buffer)
	{
		free(m_buffer);
	}
}


size_t MemoryStream::readBytes(unsigned char* buf,size_t size)
{
	size_t dataSize = m_length - m_position;
	size =MAX(0,MIN(dataSize, size));
	if (size > 0)
	{
		memcpy(buf, m_buffer + m_position, size);
		m_position += size;
	}

	return size;
}

unsigned char MemoryStream::readByte()
{
	//这里不作范围判断，在调用readByte前，检查eof。
	return *(m_buffer + m_position++);
}

void MemoryStream::writeBytes(unsigned char* buf,size_t size)
{
	size_t newSize = m_position + size;
	if (newSize > m_length) {
		if (newSize > m_capacity && ensureCapacity(newSize)) {

		}
	}

	if (size > 0)
	{
		memcpy(m_buffer + m_position, buf,  size);
		m_position += size;
	}
}

void MemoryStream::writeByte(unsigned char value)
{
	if (m_position < m_length)
	{
		*(m_buffer + m_position++) = value;
	}
}

bool MemoryStream::eof()
{
	return m_position >= m_length;
}

unsigned char* MemoryStream::getBuffer()
{
	return m_buffer;
}

bool MemoryStream::ensureCapacity(size_t size)
{
	if (size <= m_capacity) {
		return false;
	}

	if (size < 0x100) {
		size = 0x100;
	}
	if (size < m_capacity * 2) {
		size = m_capacity * 2;
	}

	unsigned char* buffer= (unsigned char*)malloc(size);
	if (buffer) {
		memcpy(buffer, m_buffer, m_capacity);
		free(m_buffer);
		m_capacity = size;
		return true;
	}

	return false;
}

NS_YH_IO_END
