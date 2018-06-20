#ifndef YH_THREAD_THREADSAFEREF_H_
#define YH_THREAD_THREADSAFEREF_H_

#include "../YHMacros.h"
#include "../platform/PlatformMacros.h"
#include "../platform/YHStdC.h"
#include "AtomicRefCount.h"

NS_YH_THREAD_BEGIN

//Ϊ�˱���ʹ��retain��release��Ϊ�麯�������̰߳�ȫref����ͨref�ֿ���
//�Ժ���Կ��ǹ�ͬ�̳�һ�����ࡣ
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