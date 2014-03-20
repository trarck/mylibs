#ifndef YH_BASE_YHOBJECT_H_
#define YH_BASE_YHOBJECT_H_

#include "Object.h"

NS_YH_BEGIN

template<typename T>
class RefObjectDeallocater {
public:
    static void deallocate(T *p) { delete p; }
};

template<typename T>
class RefArrayDeallocater {
public:
    static void deallocate(T *p) { delete[] p; }
};

/**
 * 普通指针包装成Object
 */
template <class T,typename Deallocater= RefObjectDeallocater<T> >
class RefPtr : public Object
{
public:
	inline RefPtr()
	   :m_ptr(NULL)
	{
	
	}

   inline RefPtr(T* ptr)
   :m_ptr(ptr)
   {
    
   }

   ~RefPtr(){
	   if(m_ptr)
	   {
		   Deallocater::deallocate(m_ptr);
		   m_ptr=NULL;
	   }
   }

   inline void setPtr(T* ptr){
       m_ptr=ptr;
   }

   T* getPtr()
   {
       return m_ptr;
   }

private:

   CCRef(const CCRef& other);

   CCRef& operator= (const CCRef& other){return *this;};

	T* m_ptr;
};


NS_YH_END

#endif // YH_BASE_YHOBJECT_H_
