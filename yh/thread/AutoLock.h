#ifndef YH_THREAD_AUTOLOCK_H_
#define YH_THREAD_AUTOLOCK_H_

#include "../platform/PlatformMacros.h"
#include "ThreadMacros.h"
#include "Mutex.h"

NS_YH_THREAD_BEGIN

class AutoLock
{
public:
    AutoLock(Mutex& mutex):m_mutex(mutex)
    {
        m_mutex.lock();
    }
    ~AutoLock()
    {
        m_mutex.unlock();
    }
private:
    AutoLock( const AutoLock& );
    AutoLock& operator=(const AutoLock&);
    
    Mutex& m_mutex;  
};

class AutoUnLock
{
public:
    AutoUnLock(Mutex& mutex):m_mutex(mutex)
    {
        m_mutex.unlock();
    }
    ~AutoUnLock()
    {
        m_mutex.lock();
    }
private:
    AutoUnLock( const AutoUnLock& );
    AutoUnLock& operator=(const AutoUnLock&);
    Mutex& m_mutex;  
};

NS_YH_THREAD_END
#endif //YH_THREAD_AUTOLOCK_H_
