#ifndef YH_IO_STREAM_H_
#define YH_IO_STREAM_H_

#include "../base/Ref.h"
#include "../platform/YHStdC.h"
#include "IOMacros.h"

NS_YH_IO_BEGIN

/**
 * stream base class
 */
class Stream:public Ref
{
public:
    
    Stream();

    virtual ~Stream();
    
    virtual size_t readBytes(unsigned char* buf,size_t size)=0;
    
    virtual unsigned char readByte()=0;
    
	virtual void writeBytes(unsigned char* buf,size_t size) =0;
    
    virtual void writeByte(unsigned char value) =0;

    virtual bool eof()=0;
		
    virtual void seek(size_t length);	
		
	virtual bool canSeek();

	//return the stream length
	virtual size_t getLength();

public:
	
	inline size_t getPosition()
	{
		return m_position;
	}
	
	inline void setPosition(size_t position)
	{
		m_position=position;
	}
    

protected:     
	//position for read or write
    size_t m_position;
};

NS_YH_IO_END

#endif // YH_IO_STREAM_H_
