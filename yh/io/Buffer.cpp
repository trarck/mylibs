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
    YHASSERT(position<m_size,"out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(buf,m_data+position,size);
    
    return size;
}

NS_YH_END
