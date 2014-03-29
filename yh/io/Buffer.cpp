#include "Buffer.h"
#include <string>

NS_YH_BEGIN


Buffer::Buffer(size_t size)
:m_size(size)
{
    m_data=(unsigned char*)malloc( size * sizeof(unsigned char));
}

Buffer::~Buffer()
{
    if (m_data) {
        delete m_data;
    }
}

size_t Buffer::readBytes(size_t position,void* buf,size_t size)
{
    YHASSERT(position<m_size,"Buffer::readBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memcpy(buf,m_data+position,size);
    
    return size;
}


size_t Buffer::readBytesSafe(size_t position,void* buf,size_t size)
{
    YHASSERT(position<m_size,"Buffer::readBytesSafe out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(buf,m_data+position,size);
    
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

size_t Buffer::writeBytes(size_t position,void* buf,size_t size)
{
    YHASSERT(position<m_size,"Buffer::writeBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(m_data+position,buf,size);
    
    return size;
}


NS_YH_END
