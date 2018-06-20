#include "ThreadSafeRef.h"

NS_YH_THREAD_BEGIN


ThreadSafeRef::ThreadSafeRef() : m_refCount(1) 
{

}

ThreadSafeRef::~ThreadSafeRef() 
{

}

void ThreadSafeRef::retain() 
{
    m_refCount.increment();
}

void ThreadSafeRef::release() {
    if (!m_refCount.decrement())
    {
        delete this;
    }  
}

NS_YH_THREAD_END
