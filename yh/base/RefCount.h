#ifndef YH_BASE_REFCOUNT_H_
#define YH_BASE_REFCOUNT_H_

#include <stddef.h>
#include "../YHMacros.h"

NS_YH_BEGIN

template<typename T>
class ObjectDeallocater {
public:
    static void deallocate(T *p) { delete p; }
};

template<typename T>
class ArrayDeallocater {
public:
    static void deallocate(T *p) { delete[] p; }
};

/**
 * 引用计数模板
 * 实现类似泛型的功能
 */
template <class T,typename Deallocater= ObjectDeallocater<T> >
class RefCount
{
public:
	
    RefCount()
    :_referenceCount(1)
    ,_ptr(NULL)
    {
        
    }
    
    RefCount(T* ptr)
    :_referenceCount(1)
    ,_ptr(ptr)
    {
        
    }
    
    ~RefCount();
    
    void release()
    {
        --_referenceCount;
        
        if (_referenceCount == 0)
        {
            Deallocater::deallocate(_ptr);
            delete this;
        }
    }
    
    inline void retain()
    {
        ++_referenceCount;
    }
    
    inline bool isSingleReference() const
    {
        return _referenceCount==1;
    }
    
    inline unsigned int retainCount() const {
        return getReferenceCount();
    };
    
    inline unsigned int getReferenceCount() const
    {
        return _referenceCount;
    }
    
    inline void setPtr(T* ptr)
    {
        _ptr = ptr;
    }
    
    inline T* getPtr()
    {
        return _ptr;
    }
    
protected:
    /// count of references
    unsigned int _referenceCount;
    T* _ptr;
};


NS_YH_END

#endif // YH_BASE_REFCOUNT_H_
