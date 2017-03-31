#include "Stream.h"
#include <string>

NS_YH_IO_BEGIN

Stream::Stream()
:m_position(0)
{
    
}

Stream::~Stream()
{

}

void Stream::seek(size_t length)
{
    m_position+=length;
}

	
bool Stream::canSeek()
{
	return true;
}

//return the stream length
size_t Stream::getLength()
{
	return 0;
}
NS_YH_IO_END
