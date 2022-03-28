#include "BufferStream.h"
#include <string>
#include <iostream>
NS_YH_IO_BEGIN

BufferStream::BufferStream()
:m_buffer(NULL)
{
    
}

BufferStream::BufferStream(Buffer* buffer)
: m_buffer(buffer)
{
	YH_SAFE_RETAIN(buffer);
}
	
BufferStream::~BufferStream()
{
	YH_SAFE_RELEASE_NULL(m_buffer);
}

size_t BufferStream::readBytes(unsigned char* buf,size_t size)
{
	size_t readSize = 0;
	if (m_buffer)
	{
		readSize = m_buffer->readBytes(m_position, buf, size);
		m_position += readSize;
	}
	return readSize;
}

//readByte,会有个坑，如果不检查eof，可能会取出边界外的数据。
//或者在realse版本没有asset保正m_buffer不为空，会直接崩溃。
unsigned char BufferStream::readByte()
{
	YHASSERT(m_buffer != NULL, "No buffer data");
	return m_buffer->readByte(m_position++);
}

void BufferStream::writeBytes(unsigned char* buf,size_t size)
{
	if (m_buffer)
	{
		m_position += m_buffer->writeBytes(m_position, buf, size);
	}
}

void BufferStream::writeByte(unsigned char value)
{
	if (m_buffer)
	{
		m_position += m_buffer->writeByte(value, m_position);
	}
}

bool BufferStream::eof()
{
	if (m_buffer)
	{
		return m_position >= m_buffer->getSize();
	}
	return true;
}

void BufferStream::setBuffer(Buffer* buffer)
{
	YH_SAFE_RETAIN(buffer);
	YH_SAFE_RELEASE(m_buffer);
	m_buffer = buffer;
}

Buffer* BufferStream::getBuffer()
{
	return m_buffer;
}

NS_YH_IO_END
