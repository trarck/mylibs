#ifndef YH_IO_BUFFERSTREAM_H_
#define YH_IO_BUFFERSTREAM_H_

#include "IOMacros.h"
#include "Stream.h"
#include "Buffer.h"

NS_YH_IO_BEGIN

/**
 * 流基类
 */
class BufferStream:public Stream
{
public:
    
    BufferStream();
	
	BufferStream(Buffer* buffer);

    virtual ~BufferStream();
    
    virtual size_t readBytes(unsigned char* buf,size_t size);
    
    virtual unsigned char readByte();
    
	virtual void writeBytes(unsigned char* buf,size_t size);
    
    virtual void writeByte(unsigned char value);

    virtual bool eof();

	void setBuffer(Buffer* buffer);
    
    Buffer* getBuffer();
protected:     
    Buffer* m_buffer;    
};

NS_YH_IO_END

#endif // YH_IO_BUFFERSTREAM_H_
