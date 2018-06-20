#include "Mutex.h"

NS_YH_THREAD_BEGIN

Mutex::Mutex()
  : m_mutex( new MutexImpl() )
{
    
}

Mutex::~Mutex()
{
  delete m_mutex;
}

void Mutex::lock()
{
  m_mutex->lock();
}

bool Mutex::tryLock()
{
  return m_mutex->tryLock();
}

void Mutex::unlock()
{
  m_mutex->unlock();
}

NS_YH_THREAD_END