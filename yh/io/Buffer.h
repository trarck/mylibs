#ifndef YH_IO_BUFFER_H_
#define YH_IO_BUFFER_H_

#include "../YHMacros.h"
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

    size_t readBytesSafe(size_t position,void* buf,size_t size);

    inline uint8_t readUInt8(size_t position)
    {
        YHASSERT(position<m_size,"Buffer::readUInt8 out index");
        return *(m_data+position);
    }
    
    inline uint16_t readUInt16LE(size_t position)
    {
        YHASSERT(position+2<=m_size,"Buffer::readUInt16LE out index");
        return (*(m_data+position+1) << 8) + *(m_data+position);
    }

    inline uint16_t readUInt16BE(size_t position)
    {
        YHASSERT(position+2<=m_size,"Buffer::readUInt16BE out index");
        return (*(m_data+position) << 8) + *(m_data+position+1);
    }

    inline uint32_t readUInt32LE(size_t position)
    {
        YHASSERT(position+4<=m_size,"Buffer::readUInt32LE out index");

        unsigned char* start=m_data+position;

        uint32_t val = (uint32_t)*(start+3) << 24;
        val |= (uint32_t)*(start+2) << 16;
        val |= (uint32_t)*(start+1) << 8;
        val |= *(start);

        return val;
    }

    inline uint32_t readUInt32BE(size_t position)
    {
        YHASSERT(position+4<=m_size,"Buffer::readUInt32BE out index");
                
        unsigned char* start=m_data+position;

        uint32_t val = (uint32_t)*(start) << 24;
        val |= (uint32_t)*(start+1) << 16;
        val |= (uint32_t)*(start+2) << 8;
        val |= *(start+3);

        return val;
    }

    uint64_t readUInt64LE(size_t position);

    uint64_t readUInt64BE(size_t position);

    inline size_t readUInt8(size_t position,uint8_t* val)
    {
        return readBytes(position, val, sizeof(uint8_t));
    }
    
    inline size_t readUInt16(size_t position,uint16_t* val)
    {
        return readBytes(position, val, sizeof(uint16_t));
    }

    /**
     * @brief 写入一段数据
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeBytes(size_t position,void* buf,size_t size);
    
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
