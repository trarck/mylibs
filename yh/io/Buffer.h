#ifndef YH_IO_BUFFER_H_
#define YH_IO_BUFFER_H_

#include "YHMacros.h"
#include "../base/Object.h"
#include "../base/Internals.h"
#include "../platform/YHStdC.h"

NS_YH_BEGIN

/**
 * 字节操作类
 */
class Buffer:public Object
{
public:
    
    Buffer(size_t size);
    
    ~Buffer();
    
    /**
     * @brief 读取一段数据
     * 是其它读取方法的基础
     *
     * @param position 要读取的偏移位置，从开头算起。
     * @param buf 读取后要放入的地方
     * @param size 要读取的数据大小
     *
     * @return 实际读取的大小。如果大小为0，则读取错误
     */
    size_t readBytes(size_t position,void* buf,size_t size);
    
    inline size_t readUInt8(size_t position,uint8_t* ptr)
    {
        return readBytes(position, ptr, sizeof(uint8_t));
    }
    
    size_t readUInt16(size_t position,uint16_t* ptr)
    {
        return readBytes(position, ptr, sizeof(uint16_t));
    }
    
public:
    
    inline void setSize(size_t size)
    {
        m_size = size;
    }
    
    inline size_t getSize()
    {
        return m_size;
    }
    
    inline unsigned char* getData()
    {
        return m_data;
    }
    
protected:
    
    size_t m_size;
    
    unsigned char* m_data;
};

NS_YH_END

#endif // YH_IO_BUFFER_H_
