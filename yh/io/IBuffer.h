#ifndef YH_IO_BUFFER_H_
#define YH_IO_BUFFER_H_

#include "../YHMacros.h"

NS_YH_BEGIN

#define _BUFFER_BYTE_SIZE 1
#define _BUFFER_SHORT_SIZE 2
#define _BUFFER_INT_SIZE 4
#define _BUFFER_LONG_SIZE 8


/**
 * Buffer Interface
 */
class IBuffer
{
public:

	virtual ~IBuffer(){};
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
    virtual size_t readBytes(size_t position,void* buf,size_t size) =0;

    /**
     * @brief 不安全的读取一段数据
     * 主要是使用memcpy代替memmove
     *
     * @param position 要读取的偏移位置，从开头算起。
     * @param buf 读取后要放入的地方
     * @param size 要读取的数据大小
     *
     * @return 实际读取的大小。如果大小为0，则读取错误
     */
    virtual size_t readBytesUnSafe(size_t position,void* buf,size_t size) =0;
    
    virtual unsigned char readByte(size_t position)=0;

    ////////////////////////////////////////////////////////////////
    // unsigned
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取无符号的8位整型
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint8_t readUInt8(size_t position)=0;
    
    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint16_t readUInt16LE(size_t position)=0;

    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint16_t readUInt16BE(size_t position)=0;

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint32_t readUInt32LE(size_t position)=0;
    
    //使用字节转换来读取数据，比直接计算要慢20%左右。性能估计还是消耗在memcpy上。
    //所以还是直接使用数值运算快
    virtual uint32_t readUInt32LE2(size_t position) =0;

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint32_t readUInt32BE(size_t position) =0;
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint64_t readUInt64LE(size_t position) =0;
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual uint64_t readUInt64BE(size_t position) =0;
    
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
    virtual int8_t readInt8(size_t position) =0;
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int16_t readInt16LE(size_t position) =0;
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int16_t readInt16BE(size_t position) =0;
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int32_t readInt32LE(size_t position) =0;
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int32_t readInt32BE(size_t position) =0;
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int64_t readInt64LE(size_t position) =0;
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual int64_t readInt64BE(size_t position) =0;
    
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
    virtual float readFloat16LE(size_t position) =0;
    
    /**
     * @brief 读取半精度的浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFloat16BE(size_t position) =0;
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFloatLE(size_t position) =0;
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFloatBE(size_t position) =0;
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual double readDoubleLE(size_t position) =0;
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual double readDoubleBE(size_t position) =0;
    
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
    virtual float readFixed8LE(size_t position) =0;
    
    /**
     * @brief 读取8位整型浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFixed8BE(size_t position) =0;
    
    /**
     * @brief 读取整型浮点数，占用4个字节16.16
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFixedLE(size_t position) =0;
    
    /**
     * @brief 读取整型浮点数，占用4个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    virtual float readFixedBE(size_t position) =0;
    
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
    virtual size_t writeBytes(size_t position,void* buf,size_t size) =0;
    
    /**
     * @brief 不安全写入一段数据
     * 主要使用memcpy代替memmove
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeBytesUnSafe(size_t position,void* buf,size_t size) =0;
    
    /**
     * @brief 写入一个字节
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeByte(unsigned char value,size_t position) =0;
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt8(uint8_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt16LE(uint16_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt16BE(uint16_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt32LE(uint32_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt32BE(uint32_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt64LE(uint64_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeUInt64BE(uint64_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt8(int8_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt16LE(int16_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt16BE(uint16_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt32LE(int32_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt32BE(int32_t value,size_t position) =0;

    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt64LE(int64_t value,size_t position) =0;
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeInt64BE(int64_t value,size_t position) =0;
     
    /**
     * @brief 写入半精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFloat16LE(float value,size_t position) =0;
    
    /**
     * @brief 写入半精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFloat16BE(float value,size_t position) =0;
    
    /**
     * @brief 写入单精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFloatLE(float value,size_t position) =0;
    
    /**
     * @brief 写入单精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFloatBE(float value,size_t position) =0;
    
    /**
     * @brief 写入双精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeDoubleLE(float value,size_t position) =0;
    
    /**
     * @brief 写入双精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeDoubleBE(float value,size_t position) =0;
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFixed8LE(float value,size_t position) =0;
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFixed8BE(float value,size_t position) =0;
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFixedLE(float value,size_t position) =0;
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    virtual size_t writeFixedBE(float value,size_t position) =0;
    
    /**
     * @brief 用固定值填充缓冲区
     * 会写入开始位置，但不会写入结束位置
     * @param value 要填充的数据
     * @param start 开始位置，从开头算起。
     * @param end 结束的位置，从开头算起。
     */
    virtual void fill(unsigned char value,size_t start,size_t end) =0;
    
    virtual void fill(unsigned char value,size_t start) =0;
    
    virtual void fill(unsigned char value) =0;
    
    /**
     * @brief 把当前缓存区的内容copy到目标缓存区
     * 包含开始位置，但不包含结束位置
     * @param target 目标缓存区
     * @param targetStart 目标缓存区开始位置
     * @param sourceStart 当前缓存区的开始位置。
     * @param sourceEnd 当前缓存区结束位置。
     */
    virtual void copy(Buffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd) =0;
    
    /**
     * @brief 在当前缓存区数据截取一段
     *
     * @param start 截取的开始位置。
     * @param end 截取的结束位置。
     * @param size 截取的大小。
     *
     * @return 截取段的开始指针。注意不是副本。也就是说不用删除。
     */
    virtual unsigned char* slice(size_t start,size_t* size) =0;
    
public:
    
    virtual void setSize(size_t size) =0;
    
    virtual size_t getSize() =0;
    
    virtual unsigned char* getData() =0;
    
    virtual void setData(unsigned char* data) =0;
};

NS_YH_END

#endif // YH_IO_BUFFER_H_
