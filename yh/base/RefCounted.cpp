#include "RefCounted.h"

NS_YH_BEGIN

RefCountedBase::RefCountedBase() : _refCount(0) {
#ifndef NDEBUG
  _inDtor = false;
#endif
}

RefCountedBase::~RefCountedBase() {
#ifndef NDEBUG
  DCHECK(_inDtor) << "RefCounted object deleted without calling Release()";
#endif
}

void RefCountedBase::retain() {
  // TODO(maruel): Add back once it doesn't assert 500 times/sec.
  // Current thread books the critical section "AddRelease" without release it.
  // DFAKE_SCOPED_LOCK_THREAD_LOCKED(add_release_);
#ifndef NDEBUG
  DCHECK(!_inDtor);
#endif
  ++_refCount;
}

bool RefCountedBase::release() {
  // TODO(maruel): Add back once it doesn't assert 500 times/sec.
  // Current thread books the critical section "AddRelease" without release it.
  // DFAKE_SCOPED_LOCK_THREAD_LOCKED(add_release_);
#ifndef NDEBUG
  DCHECK(!_inDtor);
#endif
  if (--_refCount == 0) {
#ifndef NDEBUG
    _inDtor = true;
#endif
    return true;
  }
  return false;
}

RefCountedThreadSafeBase::RefCountedThreadSafeBase() : _refCount(0) {
#ifndef NDEBUG
  _inDtor = false;
#endif
}

RefCountedThreadSafeBase::~RefCountedThreadSafeBase() {
#ifndef NDEBUG
  DCHECK(_inDtor) << "RefCountedThreadSafe object deleted without "
                      "calling Release()";
#endif
}

void RefCountedThreadSafeBase::retain() {
#ifndef NDEBUG
  DCHECK(!_inDtor);
#endif
  AtomicRefCountInc(&_refCount);
}

bool RefCountedThreadSafeBase::release() {
#ifndef NDEBUG
  DCHECK(!_inDtor);
  DCHECK(!AtomicRefCountIsZero(&_refCount));
#endif
  if (!AtomicRefCountDec(&_refCount)) {
#ifndef NDEBUG
    _inDtor = true;
#endif
    return true;
  }
  return false;
}

NS_YH_END
