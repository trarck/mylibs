#ifndef YH_THREAD_ATOMICS_H_
#define YH_THREAD_ATOMICS_H_

#include <atomic>
#include "ThreadMacros.h"
NS_YH_THREAD_BEGIN
class AtomicSpinLock
{
public:
  explicit AtomicSpinLock(std::atomic_flag& lock);
  ~AtomicSpinLock();
private:
  std::atomic_flag& m_Lock;
};
NS_YH_THREAD_END
#endif //YH_THREAD_ATOMICS_H_
