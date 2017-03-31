#include "MemoryStream.h"
#include <string>

NS_YH_IO_BEGIN

MemoryStream::MemoryStream()
:m_length(0)
,m_buffer(NULL)
{
    
}

MemoryStream::MemoryStream(size_t size)
	: m_length(size)
{
	m_buffer = (unsigned char*)malloc(size);
}


MemoryStream::MemoryStream(unsigned char* data, size_t size)
	:m_length(size)
{
	m_buffer = (unsigned char*)malloc(size);
	memcpy(m_buffer, data, size);
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
	size_t dataSize = m_length - m_position;
	size = MAX(0, MIN(dataSize, size));
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
NS_YH_IO_END
