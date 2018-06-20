#ifndef YH_THREAD_MUTEX_H_
#define YH_THREAD_MUTEX_H_

#include "../platform/PlatformMacros.h"
#include "ThreadMacros.h"
#include "MutexImpl.h"

NS_YH_THREAD_BEGIN

class Mutex
{
public:
    Mutex();
    ~Mutex();
    void lock();
    bool tryLock();
    void unlock();
private:
    Mutex( const Mutex& );
    Mutex& operator=(const Mutex&);
    
    MutexImpl* m_mutexImpl;  
};

NS_YH_THREAD_END
#endif //YH_THREAD_MUTEX_H_
