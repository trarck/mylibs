//暂时不使用
#ifndef YH_BASE_REFCOUNT_H_
#define YH_BASE_REFCOUNT_H_

#include "../YHMacros.h"
#include "../platform/PlatformMacros.h"

NS_YH_BEGIN
/**
*使用ref来表示根结点。
*为了效率可以取消根结点，不使用虚函数。
*/

class Ref
{
protected:
    Ref(){}
    virtual ~Ref(){}
public:
    virtual void retain(){}
    virtual bool release(){}
};

class RefCountedBase:public Ref {
protected:
    RefCountedBase();
    ~RefCountedBase();
public:
    void retain();

    // Returns true if the object should self-delete.
    bool release();

 private:
  int _refCount;
#ifndef NDEBUG
  bool _inDtor;
#endif
};

class RefCountedThreadSafeBase:public Ref {
protected:
    RefCountedThreadSafeBase();
    ~RefCountedThreadSafeBase();

    void retain();

    // Returns true if the object should self-delete.
    bool release();

 private:
  AtomicRefCount _refCount;//TODO 实现AtomicRefCount
#ifndef NDEBUG
  bool _inDtor;
#endif
};

template <class T>
class RefCounted : public RefCountedBase {
 public:
  RefCounted() { }
  ~RefCounted() { }

  void retain() {
    RefCountedBase::retain();
  }

  void release() {
    if (RefCountedBase::release()) {
      delete static_cast<T*>(this);
    }
  }
private:
    YH_DISALLOW_COPY_AND_ASSIGN(RefCounted<T>);
};

template <class T>
class RefCountedThreadSafe : public RefCountedThreadSafeBase {
 public:
  RefCountedThreadSafe() { }
  ~RefCountedThreadSafe() { }

  void retain() {
    RefCountedThreadSafeBase::retain();
  }

  void release() {
    if (RefCountedThreadSafeBase::release()) {
      delete static_cast<T*>(this);
    }
  }

private:
    YH_DISALLOW_COPY_AND_ASSIGN(RefCountedThreadSafe<T>);
};

template<typename T>
class RefCountedData : public RefCounted< RefCountedData<T> > {
public:
  RefCountedData() : data() {}
  RefCountedData(const T& in_value) : data(in_value) {}

  T data;
};

template <class T>
class scoped_refptr {
 public:
  scoped_refptr() : _ptr(NULL) {
  }

  scoped_refptr(T* p) : _ptr(p) {
    if (_ptr)
      _ptr->retain();
  }

  scoped_refptr(const scoped_refptr<T>& r) : _ptr(r._ptr) {
    if (_ptr)
      _ptr->retain();
  }

  ~scoped_refptr() {
    if (_ptr)
      _ptr->release();
  }

  T* get() const { return _ptr; }
  operator T*() const { return _ptr; }
  T* operator->() const { return _ptr; }

  scoped_refptr<T>& operator=(T* p) {
    // AddRef first so that self assignment should work
    if (p)
      p->retain();
    if (_ptr )
      _ptr ->release();
    _ptr = p;
    return *this;
  }

  scoped_refptr<T>& operator=(const scoped_refptr<T>& r) {
    return *this = r._ptr;
  }

  void swap(T** pp) {
    T* p = _ptr;
    _ptr = *pp;
    *pp = p;
  }

  void swap(scoped_refptr<T>& r) {
    swap(&r._ptr);
  }

protected:
  T* _ptr;
};

NS_YH_END

#endif // YH_BASE_REFCOUNT_H_