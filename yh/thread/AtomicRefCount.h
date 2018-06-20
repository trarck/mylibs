#ifndef YH_THREAD_ATOMICREFCOUNT_H_
#define YH_THREAD_ATOMICREFCOUNT_H_

#include "../platform/PlatformMacros.h"
#include "../platform/YHStdC.h"
#include "ThreadMacros.h"

#if defined(_WINDOWS) || defined(__APPLE__ ) || defined( HAVE_GCC_ATOMIC_BUILTINS )
#define HAVE_ATOMIC 1
#else
#define HAVE_ATOMIC 0    
#include "Mutex.h"
#include "AutoLock.h"
#endif //defined(_WINDOWS) || defined(__APPLE__ ) || defined( HAVE_GCC_ATOMIC_BUILTINS )

NS_YH_THREAD_BEGIN

class AtomicRefCount
{
public:
    AtomicRefCount();
    AtomicRefCount(int refCount);
    
    int increment();
    int decrement();
    
    int getReferenceCount() const;

private:
    //AtomicRefCount& operator=( const AtomicRefCount& );
    volatile int m_refCount;
    #if !HAVE_ATOMIC
    Mutex m_mutex;
    #endif//HAVE_ATOMIC    
};

NS_YH_THREAD_END
#endif //YH_THREAD_ATOMICREFCOUNT_H_
