#ifndef YH_THREAD_MUTEXIMPL_H_
#define YH_THREAD_MUTEXIMPL_H_

#include "../platform/PlatformMacros.h"
#include "ThreadMacros.h"

#if defined(YH_WINOWS)
#include <windows.h>
#elif defined(YH_POSIX)
#include <pthread.h>
#endif

NS_YH_THREAD_BEGIN

class MutexImpl
{
public:
    #if defined(YH_WINDOWS)
      typedef CRITICAL_SECTION LockType;
    #elif defined(YH_POSIX)
      typedef pthread_mutex_t LockType;
    #endif
        MutexImpl();
        ~MutexImpl();
        void lock();
        bool tryLock();
        void unlock();
private:
        MutexImpl( const MutexImpl& );
        MutexImpl& operator=( const MutexImpl& );

        LockType m_lock;
};

NS_YH_THREAD_END
#endif //YH_THREAD_MUTEXIMPL_H_
