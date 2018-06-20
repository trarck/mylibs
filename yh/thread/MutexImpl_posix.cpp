#include "MutexImpl.h"

NS_YH_THREAD_BEGIN

MutexImpl::MutexImpl()
{
  // For pthreads, configured the mutex to be recursive
  //  (the same thread can get it again, and just bump the ref count).
  pthread_mutexattr_t mutexAttribute;
  pthread_mutexattr_init( &mutexAttribute );
  pthread_mutexattr_settype( &mutexAttribute, PTHREAD_MUTEX_RECURSIVE );
  pthread_mutex_init( &m_mutex, &mutexAttribute );
  pthread_mutexattr_destroy( &mutexAttribute );
}

MutexImpl::~MutexImpl()
{
    pthread_mutex_destroy( &m_mutex );
}

void MutexImpl::lock()
{
    pthread_mutex_lock( &m_mutex );
}

bool MutexImpl::tryLock()
{
    return !( pthread_mutex_trylock( &m_mutex ) );
}

void MutexImpl::unlock()
{
    pthread_mutex_unlock( &m_mutex );
}

NS_YH_THREAD_END