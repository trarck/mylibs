#include "AtomicRefCount.h"

NS_YH_THREAD_BEGIN

AtomicRefCount::AtomicRefCount()
:m_refCount(0)
{

}


AtomicRefCount::AtomicRefCount(int refCount)
:m_refCount(refCount)
{
    
}

int AtomicRefCount::increment()
{
#if defined(_WINDOWS)
      return (int) InterlockedIncrement( (volatile LONG*)&m_refCount );
#elif defined( __APPLE__ )
      return (int) OSAtomicIncrement32Barrier( (volatile int32_t*)&m_refCount );
#elif defined( HAVE_GCC_ATOMIC_BUILTINS )
      // Use the gcc intrinsic for atomic increment if supported.
      return (int) __sync_add_and_fetch( &m_refCount, 1 );
#else
      // Fallback to using a lock
      AutoLock m( m_lock );
      return ++m_refCount;
#endif
}

int AtomicRefCount::decrement()
{
#if defined( _WINDOWS ) 
      return (int) InterlockedDecrement( (volatile LONG*)&m_refCount );
#elif defined( __APPLE__ )
      return (int) OSAtomicDecrement32Barrier( (volatile int32_t*)&m_refCount );
#elif defined( HAVE_GCC_ATOMIC_BUILTINS )
      // Use the gcc intrinsic for atomic decrement if supported.
      return (int) __sync_sub_and_fetch( &m_refCount, 1 );
#else
      // Fallback to using a lock
      AutoLock m( m_lock );
      return --m_refCount;
#endif
}

int AtomicRefCount::getReferenceCount() const
{
    return m_refCount;
}
    
NS_YH_THREAD_END