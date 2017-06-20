#ifndef YH_IO_MEMORYSTREAM_H_
#define YH_IO_MEMORYSTREAM_H_

#include "IOMacros.h"
#include "Stream.h"


NS_YH_IO_BEGIN

/**
 * 流基类
 */
class MemoryStream:public Stream
{
public:
    
    MemoryStream();
	
	MemoryStream(size_t size);
    
    MemoryStream(unsigned char* data,size_t size);

    virtual ~MemoryStream();	
    
    virtual size_t readBytes(unsigned char* buf,size_t size);
    
    virtual unsigned char readByte();
    
	virtual void writeBytes(unsigned char* buf, size_t size);
    
    virtual void writeByte(unsigned char value);

    virtual bool eof();
   
	unsigned char* getBuffer();
protected:     
	size_t m_length;
	unsigned char* m_buffer;
};

NS_YH_IO_END

#endif // YH_IO_MEMORYSTREAM_H_
