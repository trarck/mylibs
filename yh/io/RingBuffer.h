#ifndef YH_IO_RING_BUFFER_H_
#define YH_IO_RING_BUFFER_H_

#include "../YHMacros.h"
#include "../base/Ref.h"
#include "../base/Internals.h"
#include "../platform/YHStdC.h"
#include "IeeeHalfPrecision.h"

NS_YH_BEGIN

#define RING_BUFFER_BYTE_SIZE 1
#define RING_BUFFER_SHORT_SIZE 2
#define RING_BUFFER_INT_SIZE 4
#define RING_BUFFER_LONG_SIZE 8


/**
 * 字节操作类
 */
class RingBuffer:public Ref
{
public:
    
	RingBuffer();
    
	RingBuffer(size_t capacity);
    
    ~RingBuffer();
    
    /**
     * @brief 读取一段数据
     * 是其它读取方法的基础
     *
     * @param buf 读取后要放入的地方
     * @param size 要读取的数据大小
     *
     * @return 实际读取的大小。如果大小为0，则读取错误
     */
    size_t readBytes(void* buf,size_t size);
   
    inline unsigned char readByte()
    {
		YHASSERT(getSize(), "RingBuffer::readByte out index");
		unsigned char* start = m_data + m_headPosition;
		moveHeadPosition(RING_BUFFER_BYTE_SIZE);
		return *(start);
    }

    ////////////////////////////////////////////////////////////////
    // unsigned
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取无符号的8位整型
     *
     * @return 读取的值
     */
    inline uint8_t readUInt8()
    {
        YHASSERT(getSize(),"RingBuffer::readUInt8 out index");
		unsigned char* start = m_data + m_headPosition;
		moveHeadPosition(RING_BUFFER_BYTE_SIZE);
        return *(start);
    }
    
    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用小端保存
     *
     * @return 读取的值
     */
	uint16_t readUInt16LE();

    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用大端保存
     *
     * @return 读取的值
     */
	uint16_t readUInt16BE();

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用小端保存
     *
     * @return 读取的值
     */
	uint32_t readUInt32LE();
    
    //使用字节转换来读取数据，比直接计算要慢20%左右。性能估计还是消耗在memcpy上。
    //所以还是直接使用数值运算快
	uint32_t readUInt32LE2();

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
	uint32_t readUInt32BE();
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    uint64_t readUInt64LE();
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    uint64_t readUInt64BE();
    
    ////////////////////////////////////////////////////////////////
    // signed
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取有符号的8位整型
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int8_t readInt8()
    {
        return (int8_t)(readUInt8());
//        uint8_t val=readUInt8(position);
//        return (val & 0x80)?val:(0xff-val+1)*-1;
    }
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int16_t readInt16LE()
    {
        return (int16_t)readUInt16LE();
    }
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int16_t readInt16BE()
    {
        return (int16_t)readUInt16BE();
    }
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int32_t readInt32LE()
    {
        return (int32_t)readUInt32LE();
    }
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int32_t readInt32BE()
    {
        return (int32_t)readUInt32BE();
    }
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int64_t readInt64LE()
    {
        return (int64_t)readUInt64LE();
    }
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int64_t readInt64BE()
    {
        return (int64_t)readUInt64BE();
    }

    
    ////////////////////////////////////////////////////////////////
    // float
    ////////////////////////////////////////////////////////////////
    /**
     * @brief 读取半精度的浮点数，占用2个字节
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloat16LE()
    {
        YHASSERT(position+RING_BUFFER_SHORT_SIZE<=m_size,"Buffer::readFloat16LE out index");
        
        uint16_t halfInt=readUInt16LE();
        
        float val;
        
        //半精度转单精度
        halfp2singles(&val, &halfInt);
        
        return val;
    }
    
    /**
     * @brief 读取半精度的浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloat16BE(size_t position)
    {
        YHASSERT(position+RING_BUFFER_SHORT_SIZE<=m_size,"Buffer::readFloat16BE out index");
//        uint16_t halfInt=readUInt16BE(position);
//        
//        uint32_t singleInt=0;
//        
//        //半精度转单精度
//        halfp2singlesTyped(&singleInt, &halfInt);
//                
//        return bitwise_cast<uint32_t,float>(singleInt);
        
        uint16_t halfInt=readUInt16BE(position);
        
        float val;
        
        //半精度转单精度
        halfp2singles(&val, &halfInt);
        
        return val;
    }
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloatLE(size_t position)
    {
        YHASSERT(position+RING_BUFFER_INT_SIZE<=m_size,"Buffer::readFloatLE out index");
        return byteToFloat<float,kLittleEndian>(m_data+position);
    }
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloatBE(size_t position)
    {
        YHASSERT(position+RING_BUFFER_INT_SIZE<=m_size,"Buffer::readFloatBE out index");
        return byteToFloat<float,kBigEndian>(m_data+position);
    }
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline double readDoubleLE(size_t position)
    {
        YHASSERT(position+8<=m_size,"Buffer::readDoubleLE out index");
        return byteToFloat<double,kLittleEndian>(m_data+position);
    }
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline double readDoubleBE(size_t position)
    {
        YHASSERT(position+8<=m_size,"Buffer::readDoubleBE out index");
        return byteToFloat<double,kBigEndian>(m_data+position);
    }
    
    ////////////////////////////////////////////////////////////////
    // fixed float 整型表示浮点数
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取8位整型浮点数，占用2个字节.8.8
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixed8LE(size_t position)
    {
        return (float)readUInt16LE(position)/0x100;
    }
    
    /**
     * @brief 读取8位整型浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixed8BE(size_t position)
    {
        return (float)readUInt16BE(position)/0x100;
    }
    
    /**
     * @brief 读取整型浮点数，占用4个字节16.16
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixedLE(size_t position)
    {
        return (float)readUInt32LE(position)/0x10000;
    }
    
    /**
     * @brief 读取整型浮点数，占用4个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixedBE(size_t position)
    {
        return (float)readUInt32BE(position)/0x10000;
    }
    
    
//    ////////////////////////////////////////////////////////////////
//    // 使用字节操作
//    ////////////////////////////////////////////////////////////////
//    inline size_t readUInt8(size_t position,uint8_t* val)
//    {
//        return readBytes(position, val, sizeof(uint8_t));
//    }
//    
//    inline size_t readUInt16LE(size_t position,uint16_t* val)
//    {
//        unsigned char buf[2];
//        
//        size_t ret=readBytes(position, buf, sizeof(uint16_t));
//        
//        if (kLittleEndian!=getEndianness()) {
//            swizzle(buf, 2);
//        }
//        
//        *val=*buf;
//        
//        return ret;
//    }
//    
//    inline size_t readUInt16BE(size_t position,uint16_t* val)
//    {
//        unsigned char buf[2];
//        
//        size_t ret=readBytes(position, buf, sizeof(uint16_t));
//        
//        if (kBigEndian!=getEndianness()) {
//            swizzle(buf, 2);
//        }
//        
//        *val=*buf;
//        
//        return ret;
//    }
    
    /**
     * @brief 写入一段数据
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeBytes(size_t position,void* buf,size_t size);
    
    /**
     * @brief 不安全写入一段数据
     * 主要使用memcpy代替memmove
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeBytesUnSafe(size_t position,void* buf,size_t size);
    
    /**
     * @brief 写入一个字节
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeByte(unsigned char value,size_t position)
    {
        YHASSERT(position<m_size,"Buffer::writeByte out index");
        
        *(m_data+position)=value;
        
        return RING_BUFFER_BYTE_SIZE;
    }
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt8(uint8_t value,size_t position)
    {
        YHASSERT(position<m_size,"Buffer::writeUInt8 out index");
        
        *(m_data+position)=value;
        
        return RING_BUFFER_BYTE_SIZE;
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt16LE(uint16_t value,size_t position)
    {
        YHASSERT(position+RING_BUFFER_SHORT_SIZE<=m_size,"Buffer::writeUInt16LE out index");
        
        unsigned char* start=m_data+position;
        
        *(start) = value & 0x00FF;
        *(start+1) = (value & 0xFF00) >> 8;
        
        return RING_BUFFER_SHORT_SIZE;
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt16BE(uint16_t value,size_t position)
    {
        YHASSERT(position+RING_BUFFER_SHORT_SIZE<=m_size,"Buffer::writeUInt16BE out index");
        
        unsigned char* start=m_data+position;
        
        *(start) = (value & 0xFF00) >> 8;
        *(start+1) = value & 0x00FF;
        
        return RING_BUFFER_SHORT_SIZE;
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt32LE(uint32_t value,size_t position)
    {
        YHASSERT(position+RING_BUFFER_INT_SIZE<=m_size,"Buffer::writeUInt32LE out index");
        
        unsigned char* start=m_data+position;
        
        *(start) = value & 0xFF;
        *(start+1) = (value >> 8 ) & 0xFF;
        *(start+2) = (value >> 16 ) & 0xFF;
        *(start+3) = (value >> 24 ) & 0xFF;
        
        return RING_BUFFER_INT_SIZE;
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt32BE(uint32_t value,size_t position)
    {
        YHASSERT(position+RING_BUFFER_INT_SIZE<=m_size,"Buffer::writeUInt32BE out index");
        
        unsigned char* start=m_data+position;
        
        *(start) = (value >> 24 ) & 0xFF;
        *(start+1) = (value >> 16 ) & 0xFF;
        *(start+2) = (value >> 8 ) & 0xFF;
        *(start+3) = value & 0xFF;
        
        return RING_BUFFER_INT_SIZE;
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeUInt64LE(uint64_t value,size_t position);
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeUInt64BE(uint64_t value,size_t position);
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt8(int8_t value,size_t position)
    {
        return writeUInt8((uint8_t)value, position);
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt16LE(int16_t value,size_t position)
    {
        return writeUInt16LE((uint16_t)value, position);
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt16BE(uint16_t value,size_t position)
    {
        return writeUInt16BE((uint16_t)value, position);
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt32LE(int32_t value,size_t position)
    {
        return writeUInt32LE((uint32_t)value, position);
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt32BE(int32_t value,size_t position)
    {
        return writeUInt32BE((uint32_t)value, position);
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt64LE(int64_t value,size_t position)
    {
        return writeUInt64LE((uint64_t)value, position);
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt64BE(int64_t value,size_t position)
    {
        return writeUInt64BE((uint64_t)value, position);
    }
    
    /**
     * @brief 写入半精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloat16LE(float value,size_t position)
    {
        uint16_t halfInt=0;
        singles2halfp(&halfInt, &value);
        
        return writeUInt16LE(halfInt, position);
    }
    
    /**
     * @brief 写入半精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloat16BE(float value,size_t position)
    {
        uint16_t halfInt=0;
        singles2halfp(&halfInt, &value);
        
        return writeUInt16BE(halfInt, position);
    }
    
    /**
     * @brief 写入单精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloatLE(float value,size_t position)
    {
        unsigned char buf[4];
        
        floatToByte<float, kLittleEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 4);
    }
    
    /**
     * @brief 写入单精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloatBE(float value,size_t position)
    {
        unsigned char buf[4];
        
        floatToByte<float, kBigEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 4);
    }
    
    /**
     * @brief 写入双精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeDoubleLE(float value,size_t position)
    {
        unsigned char buf[8];
        
        floatToByte<double, kLittleEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 8);
    }
    
    /**
     * @brief 写入双精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeDoubleBE(float value,size_t position)
    {
        unsigned char buf[8];
        
        floatToByte<double, kBigEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 8);
    }
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixed8LE(float value,size_t position)
    {
        uint16_t fixedInt= (uint16_t)(value * 0x100);
        
        return writeUInt16LE(fixedInt, position);
    }
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixed8BE(float value,size_t position)
    {
        uint16_t fixedInt= (uint16_t)(value * 0x100);
        
        return writeUInt16BE(fixedInt, position);
    }
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixedLE(float value,size_t position)
    {
        uint32_t fixedInt= (uint32_t)(value * 0x10000);
        
        return writeUInt32LE(fixedInt, position);
    }
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixedBE(float value,size_t position)
    {
        uint32_t fixedInt= (uint32_t)(value * 0x10000);
        
        return writeUInt32BE(fixedInt, position);
    }
    
    /**
     * @brief 用固定值填充缓冲区
     * 会写入开始位置，但不会写入结束位置
     * @param value 要填充的数据
     * @param start 开始位置，从开头算起。
     * @param end 结束的位置，从开头算起。
     */
    void fill(unsigned char value,size_t start,size_t end);
    
    inline void fill(unsigned char value,size_t start)
    {
        fill(value, start, m_size);
    }
    
    inline void fill(unsigned char value)
    {
        fill(value, 0, m_size);
    }
    
    /**
     * @brief 把当前缓存区的内容copy到目标缓存区
     * 包含开始位置，但不包含结束位置
     * @param target 目标缓存区
     * @param targetStart 目标缓存区开始位置
     * @param sourceStart 当前缓存区的开始位置。
     * @param sourceEnd 当前缓存区结束位置。
     */
    void copy(Buffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd);
    
    /**
     * @brief 在当前缓存区数据截取一段
     *
     * @param start 截取的开始位置。
     * @param end 截取的结束位置。
     * @param size 截取的大小。
     *
     * @return 截取段的开始指针。注意不是副本。也就是说不用删除。
     */
    unsigned char* slice(size_t start,size_t* size);
	size_t getSize();
public:
    
    inline unsigned char* getData()
    {
        return m_data;
    }

protected:
	inline void moveHeadPosition(size_t offset)
	{
		m_headPosition += offset;
		if (m_headPosition >=m_capacity)
		{
			m_headPosition -= m_capacity;
		}
	}

	inline void moveTailPosition(size_t offset)
	{
		m_tailPosition += offset;
		if (m_tailPosition >= m_capacity)
		{
			m_tailPosition -= m_capacity;
		}
	}
protected:
	size_t m_capacity;
	unsigned char* m_data;
	size_t m_headPosition;
	size_t m_tailPosition;
};

NS_YH_END

#endif // YH_IO_RING_BUFFER_H_
