#include "Ref.h"

NS_YH_BEGIN

Ref::Ref()
:_referenceCount(1) // when the object is created, the reference count of it is 1
{
    static unsigned int uObjectCount = 0;

    _id = ++uObjectCount;
}

Ref::~Ref()
{

}

void Ref::release()
{
    --_referenceCount;
    
    if (_referenceCount == 0)
    {
        delete this;
    }
}

unsigned int Ref::getReferenceCount() const
{
    return _referenceCount;
}

bool Ref::isEqual(const Ref *object)
{
    return this == object;
}

NS_YH_END
