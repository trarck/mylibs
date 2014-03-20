#ifndef YH_BASE_YHOBJECT_H_
#define YH_BASE_YHOBJECT_H_

#include "Object.h"

NS_YH_BEGIN

/**
 * 普通指针包装成Object
 */
template <class T>
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
		   delete m_ptr;
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
