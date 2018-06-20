#include "MutexImpl.h"

NS_YH_THREAD_BEGIN

MutexImpl::MutexImpl()
{
    InitializeCriticalSection( &m_lock );
}

MutexImpl::~MutexImpl()
{
    DeleteCriticalSection( &m_lock );
}

void MutexImpl::lock()
{
    EnterCriticalSection( &m_lock );
}

bool MutexImpl::tryLock()
{
    return TryEnterCriticalSection( &m_lock ) ? true : false;
}

void MutexImpl::unlock()
{
    LeaveCriticalSection( &m_lock );
}

NS_YH_THREAD_END