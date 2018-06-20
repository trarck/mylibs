#include "Mutex.h"

NS_YH_THREAD_BEGIN

Mutex::Mutex()
  : m_mutexImpl( new MutexImpl() )
{
    
}

Mutex::~Mutex()
{
  delete m_mutexImpl;
}

void Mutex::lock()
{
	m_mutexImpl->lock();
}

bool Mutex::tryLock()
{
  return m_mutexImpl->tryLock();
}

void Mutex::unlock()
{
	m_mutexImpl->unlock();
}

NS_YH_THREAD_END