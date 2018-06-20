#ifndef YH_THREAD_THREADSAFEREF_H_
#define YH_THREAD_THREADSAFEREF_H_

#include "../YHMacros.h"
#include "../platform/PlatformMacros.h"
#include "../platform/YHStdC.h"
#include "AtomicRefCount.h"

NS_YH_THREAD_BEGIN

//为了避免使用retain，release成为虚函数，把线程安全ref和普通ref分开。
//以后可以考虑共同继承一个基类。
class ThreadSafeRef{
protected:
	ThreadSafeRef();
	virtual ~ThreadSafeRef();

	void retain();

	void release();
private:
    AtomicRefCount m_refCount;
};

NS_YH_THREAD_END

#endif // YH_THREAD_THREADSAFEREF_H_