#ifndef YH_BASE_RCPTR_H_
#define YH_BASE_RCPTR_H_

NS_YH_BEGIN

/**
 * Object包装成值对象。
 * 用于std vector map的元素。
 * 类似智能指针
 */

/**
 * A reference counting-managed pointer for classes derived from RCBase which can
 * be used as C pointer
 * Original code: http://www.codeproject.com/Articles/64111/Building-a-Quick-and-Handy-Reference-Counting-Clas
 * License: http://www.codeproject.com/info/cpol10.aspx
 */
template < class T >
class RCPtr
{
public:
	//Construct using a C pointer
	//e.g. RCPtr< T > x = new T();
	RCPtr(T* ptr = nullptr)
    : _ptr(ptr)
	{
        if(ptr != nullptr) {ptr->retain();}
	}

	//Copy constructor
	RCPtr(const RCPtr &ptr)
    : _ptr(ptr._ptr)
	{
//        printf("Array: copy constructor: %p\n", this);
		if(_ptr != NULL) {_ptr->retain();}
	}

    //Move constructor
//	RCPtr(RCPtr &&ptr)
//    : _ptr(ptr._ptr)
//	{
////        printf("Array: Move Constructor: %p\n", this);
//        ptr._ptr = nullptr;
//	}

	~RCPtr()
	{
//        printf("Array: Destructor: %p\n", this);
        if(_ptr != NULL) {_ptr->release();}
	}

	//Assign a pointer
	//e.g. x = new T();
	RCPtr &operator=(T* ptr)
	{
//        printf("Array: operator= T*: %p\n", this);

        //The following grab and release operations have to be performed
        //in that order to handle the case where ptr == _ptr
        //(See comment below by David Garlisch)
        if(ptr != NULL) {ptr->retain();}
        if(_ptr != NULL) {_ptr->release();}
        _ptr = ptr;
        return (*this);
	}

	//Assign another RCPtr
	RCPtr &operator=(const RCPtr &ptr)
	{
//        printf("Array: operator= const&: %p\n", this);
        return (*this) = ptr._ptr;
	}

	//Retrieve actual pointer
	T* get() const
	{
        return _ptr;
	}

    //Some overloaded operators to facilitate dealing with an RCPtr
    //as a conventional C pointer.
    //Without these operators, one can still use the less transparent
    //get() method to access the pointer.
    T* operator->() const {return _ptr;}		//x->member
    T &operator*() const {return *_ptr;}		//*x, (*x).member
    explicit operator T*() const {return _ptr;}		//T* y = x;
    explicit operator bool() const {return _ptr != NULL;}	//if(x) {/*x is not NULL*/}
    bool operator==(const RCPtr &ptr) {return _ptr == ptr._ptr;}
    bool operator==(const T *ptr) {return _ptr == ptr;}

private:
    T *_ptr;	//Actual pointer
};


NS_YH_END

#endif // YH_BASE_RCPTR_H_
