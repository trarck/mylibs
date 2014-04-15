#include "Array.h"

NS_YH_BEGIN

Array::Array()
: m_data(NULL)
{
    init();
}


Array::~Array()
{
    YHDEBUG("deallocing Array: %p - len: %d", this, count() );
}
//
//Array* Array::create()
//{
//    Array* array = new Array();
//
//    if (array && array->initWithCapacity(7))
//    {
////        array->autorelease();
//    }
//    else
//    {
//        YH_SAFE_DELETE(array);
//    }
//    
//    return array;
//}
//
//Array* Array::createWithObject(Object* object)
//{
//    Array* array = new Array();
//
//    if (array && array->initWithObject(object))
//    {
////        array->autorelease();
//    }
//    else
//    {
//        YH_SAFE_DELETE(array);
//    }
//
//    return array;
//}
//
//Array* Array::create(Object* object, ...)
//{
//    va_list args;
//    va_start(args,object);
//
//    Array* array = create();
//    if (array && object)
//    {
//        array->addObject(object);
//        Object *i = va_arg(args, Object*);
//        while (i) 
//        {
//            array->addObject(i);
//            i = va_arg(args, Object*);
//        }
//    }
//    else
//    {
//        YH_SAFE_DELETE(array);
//    }
//
//    va_end(args);
//
//    return array;
//}
//
//Array* Array::createWithCapacity(int capacity)
//{
//    YHASSERT(capacity>=0, "Invalid capacity");
//
//    Array* array = new Array();
//    
//    if (array && array->initWithCapacity(capacity))
//    {
////        array->autorelease();
//    }
//    else
//    {
//        YH_SAFE_DELETE(array);
//    }
//    
//    return array;
//}
//
//Array* Array::createWithContentsOfFile(const std::string& fileName)
//{
//    Array* ret = Array::createWithContentsOfFileThreadSafe(fileName);
//    if (ret != NULL)
//    {
////        ret->autorelease();
//    }
//    return ret;
//}
//
//Array* Array::createWithContentsOfFileThreadSafe(const std::string& fileName)
//{
////    return FileUtils::getInstance()->createArrayWithContentsOfFile(fileName);
//    return NULL;
//}

bool Array::init()
{
    return initWithCapacity(7);
}

bool Array::initWithObject(Object* object)
{
    bool ret = initWithCapacity(7);
    if (ret)
    {
        addObject(object);
    }
    return ret;
}

/** Initializes an array with some objects */
bool Array::initWithObjects(Object* object, ...)
{
    bool ret = false;
    do 
    {
        if(object == NULL) break;

        va_list args;
        va_start(args, object);

        if (object)
        {
            this->addObject(object);
            Object* i = va_arg(args, Object*);
            while (i) 
            {
                this->addObject(i);
                i = va_arg(args, Object*);
            }
            ret = true;
        }
        va_end(args);

    } while (false);

    return ret;
}

bool Array::initWithCapacity(int capacity)
{
    YHASSERT(capacity>=0, "Invalid capacity");

    m_data.reserve(capacity);
    return true;
}

bool Array::initWithArray(Array* otherArray)
{
    m_data = otherArray->getData();
    return true;
}

int Array::getIndexOfObject(Object* object) const
{
    const_iterator it = m_data.begin();

    for (int i = 0; it != m_data.end(); ++it, ++i)
    {
        if (*it == object)
        {
            return i;
        }
    }
    
    return -1;
}

Object* Array::getRandomObject()
{
    if (m_data.size()==0)
    {
        return NULL;
    }

    float r = ((float)rand()/RAND_MAX);
    
    if (r == 1) // to prevent from accessing data-arr[data->num], out of range.
    {
        r = 0;
    }

    r *= m_data.size();
    
    return m_data.at(r);
}

bool Array::containsObject(Object* object) const
{
    int i = this->getIndexOfObject(object);
    return (i >= 0);
}

bool Array::isEqualToArray(Array* otherArray)
{
    for (size_t i = 0; i < this->count(); ++i)
    {
        if (!this->getObjectAtIndex(i)->isEqual(otherArray->getObjectAtIndex(i)))
        {
            return false;
        }
    }
    return true;
}

void Array::addObject(Object* object)
{
    m_data.pushBack(object);
}

void Array::addObjectsFromArray(Array* otherArray)
{
    for (iterator iter=otherArray->begin(); iter!=otherArray->end(); ++iter) {
        m_data.pushBack(*iter);
    }
}

void Array::insertObject(Object* object, int index)
{
    m_data.insert(index, object);
}

void Array::setObject(Object* object, int index)
{
    m_data.replace(index, object);
}

void Array::removeLastObject(bool releaseObj)
{
    YHASSERT(m_data.size(), "no objects added");
    m_data.popBack();
}

void Array::removeObject(Object* object, bool releaseObj /* ignored */)
{
    m_data.eraseObject(object,releaseObj);
}

void Array::removeObjectAtIndex(size_t index, bool releaseObj /* ignored */)
{
    m_data.erase(index);
}

void Array::removeObjectsInArray(Array* otherArray)
{
    YHASSERT(false, "not implemented");
}

void Array::removeAllObjects()
{
    m_data.clear();
}

void Array::fastRemoveObjectAtIndex(int index)
{
    removeObjectAtIndex(index);
}

void Array::fastRemoveObject(Object* object)
{
    removeObject(object);
}

void Array::exchangeObject(Object* object1, Object* object2)
{
    m_data.swap(object1, object2);
}

void Array::exchangeObjectAtIndex(size_t index1, size_t index2)
{
    m_data.swap(index1, index2);
}

void Array::replaceObjectAtIndex(int index, Object* object, bool releaseObject /* ignored */)
{
    m_data.replace(index, object);
}

void Array::reverseObjects()
{
    m_data.reverse();
}

void Array::reduceMemoryFootprint()
{
    // N/A
}

Array* Array::clone() const
{
    Array* ret = new Array();
//    ret->autorelease();
    ret->initWithCapacity(m_data.size() > 0 ? (int)m_data.size() : 1);

    Object* obj = NULL;
    Object* tmpObj = NULL;
    Clonable* clonable = NULL;
    
    for (const_iterator iter=m_data.begin(); iter!=m_data.end(); ++iter) {
        
        obj=(*iter);
        
        clonable = dynamic_cast<Clonable*>(obj);
        if (clonable)
        {
            tmpObj = dynamic_cast<Object*>(clonable->clone());
            if (tmpObj)
            {
                ret->addObject(tmpObj);
            }
        }
        else
        {
            YHDEBUG("%s isn't clonable.", typeid(*obj).name());
        }
    }

    return ret;
}

NS_YH_END
