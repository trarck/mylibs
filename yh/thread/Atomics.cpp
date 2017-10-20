#include "Atomics.h"

NS_YH_THREAD_BEGIN
///////////////////////////////////////////////////////////////////////////
// Fast spinlock implementation. No backoff when busy
///////////////////////////////////////////////////////////////////////////
CAtomicSpinLock::CAtomicSpinLock(std::atomic_flag& lock) : m_Lock(lock)
{
  while (atomic_flag_test_and_set(&m_Lock)) {} // Lock
}

CAtomicSpinLock::~CAtomicSpinLock()
{
  std::atomic_flag_clear(&m_Lock); // Unlock
}
