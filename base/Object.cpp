#include "Object.h"

NS_YH_BEGIN

Object::Object()
:_referenceCount(1) // when the object is created, the reference count of it is 1
{
    static unsigned int uObjectCount = 0;

    _id = ++uObjectCount;
}

Object::~Object()
{

}

void Object::release()
{
    --_referenceCount;
    
    if (_referenceCount == 0)
    {
        delete this;
    }
}

unsigned int Object::getReferenceCount() const
{
    return _referenceCount;
}

bool Object::isEqual(const YHObject *object)
{
    return this == object;
}

NS_YH_END
