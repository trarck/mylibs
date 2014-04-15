#ifndef YH_COLLECTIONS_BASEARRAY_H_
#define YH_COLLECTIONS_BASEARRAY_H_

#include "../YHMacros.h"
#include "../base/Object.h"
#include "Vector.h"

NS_YH_BEGIN

template<class T>
class BaseArray : public Object
{
public:
    
    BaseArray()
    : m_data(NULL)
    {
        init();
    }
    
    /**
     */
    ~BaseArray()
    {
        
    }
    
    /** 
     * @brief Creates an empty array.s
     */
    static BaseArray* create()
    {
        Array* array = new Array();
        
        if (array && array->initWithCapacity(7))
        {
            //        array->autorelease();
        }
        else
        {
            YH_SAFE_DELETE(array);
        }
        
        return array;
    }
    
    /** 
     * @brief Create an array with objects 
     */
    static BaseArray* create(T* object, ...)
    {
        va_list args;
        va_start(args,object);
        
        Array* array = create();
        if (array && object)
        {
            array->addObject(object);
            Object *i = va_arg(args, Object*);
            while (i)
            {
                array->addObject(i);
                i = va_arg(args, Object*);
            }
        }
        else
        {
            YH_SAFE_DELETE(array);
        }
        
        va_end(args);
        
        return array;
    }
    
    /**
     * @brief Create an array with one object 
     */
    static BaseArray* createWithObject(T* object)
    {
        Array* array = new Array();
        
        if (array && array->initWithObject(object))
        {
            //        array->autorelease();
        }
        else
        {
            YH_SAFE_DELETE(array);
        }
        
        return array;
    }
    
    /** 
     * @brief Create an array with a default capacity 
     */
    static BaseArray* createWithCapacity(int capacity);
    {
        YHASSERT(capacity>=0, "Invalid capacity");
        
        Array* array = new Array();
        
        if (array && array->initWithCapacity(capacity))
        {
            //        array->autorelease();
        }
        else
        {
            YH_SAFE_DELETE(array);
        }
        
        return array;
    }
    
    /** Create an array with from an existing array 
     */
    static BaseArray* createWithArray(BaseArray* otherArray)
    {
        return otherArray->clone();
    }
    
    /** 
     * @brief Initializes an array
     */
    bool init()
    {
        return initWithCapacity(7);
    }
    
    /** 
     @brief Initializes an array with one object
     */
    bool initWithObject(T* object)
    {
        bool ret = initWithCapacity(7);
        if (ret)
        {
            addObject(object);
        }
        return ret;
    }
    
    /** 
     @brief Initializes an array with some objects
     */
    bool initWithObjects(T* object, ...)
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
    
    /** 
     @brief Initializes an array with capacity
     */
    bool initWithCapacity(int capacity)
    {
        YHASSERT(capacity>=0, "Invalid capacity");
        
        m_data.reserve(capacity);
        return true;
    }
    
    /** 
     @breif Initializes an array with an existing array
     */
    bool initWithArray(BaseArray* otherArray)
    {
        m_data = otherArray->getData();
        return true;
    }


    /** 
     @brief Returns element count of the array
     */
    size_t count() const
    {
        return data.size();
    }
    
    /** 
     @return Returns capacity of the array
     */
    size_t capacity() const
    {
        return data.capacity();
    }
    /** 
     @return Returns index of a certain object, return UINT_MAX if doesn't contain the object
     */
    int getIndexOfObject(T* object) const
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

    /** 
     @return Returns an element with a certain index
     */
    T* getObjectAtIndex(size_t index)
    {
        CCASSERT(index>=0 && index < count(), "index out of range in getObjectAtIndex()");
        return data[index].get();
    }

    /** 
     @return Returns the last element of the array
     */
    T* getLastObject()
    {
        return data.back().get();
    }

    /** 
     @return Returns a random element
     */
    T* getRandomObject()
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

    /** 
     @return Returns a Boolean value that indicates whether object is present in array.
     */
    bool containsObject(T* object) const
    {
        int i = this->getIndexOfObject(object);
        return (i >= 0);
    }

    bool isEqualToArray(BaseArray* otherArray)
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
    
    
    // Adding Objects

    /** 
     @brief Add a certain object
     */
    void addObject(T* object)
    {
        m_data.pushBack(object);
    }

    /** 
     @brief Add all elements of an existing array
     */
    void addObjectsFromArray(BaseArray* otherArray)
    {
        for (iterator iter=otherArray->begin(); iter!=otherArray->end(); ++iter) {
            m_data.pushBack(*iter);
        }
    }
    
    /** 
     @brief Insert a certain object at a certain index
     */
    void insertObject(T* object, size_t index)
    {
        m_data.insert(index, object);
    }
    
    /** 
     @brief sets a certain object at a certain index
     */
    void setObject(T* object, size_t index)
    {
        m_data.replace(index, object);
    }
    
    /** 
     @brief sets a certain object at a certain index without retaining. Use it with caution
     */
    void fastSetObject(T* object, size_t index)
    {
        setObject(object, index);
    }

    // Removing Objects

    /** 
     @brief Remove last object
     */
    void removeLastObject(bool releaseObj = true)
    {
        YHASSERT(m_data.size(), "no objects added");
        m_data.popBack();
    }
    
    /** 
     @brief Remove a certain object
     */
    void removeObject(T* object, bool releaseObj = true)
    {
        m_data.eraseObject(object,releaseObj);
    }
    
    /** 
     @brief Remove an element with a certain index
     */
    void removeObjectAtIndex(size_t index, bool releaseObj = true)
    {
        m_data.erase(index);
    }
    
    /** 
     @brief Remove all elements
     */
    void removeObjectsInArray(BaseArray* otherArray)
    {
        for (iterator iter=otherArray->begin(); iter!=otherArray->end(); ++iter) {
            m_data.eraseObject(*iter);
        }
    }
    
    /** 
     @brief Remove all objects
     */
    void removeAllObjects()
    {
        m_data.clear();
    }
    
    /** 
     @brief Fast way to remove a certain object
     */
    void fastRemoveObject(T* object)
    {
        removeObject(object);
    }
    
    /** 
     * Fast way to remove an element with a certain index
     */
    void fastRemoveObjectAtIndex(size_t index)
    {
        removeObjectAtIndex(index);
    }
    
    // Rearranging Content

    /** 
     Swap two elements
     */
    void exchangeObject(T* object1, T* object2)
    {
        m_data.swap(object1, object2);
    }
    
    /** 
     * Swap two elements with certain indexes
     */
    void exchangeObjectAtIndex(size_t index1, size_t index2)
    {
        m_data.swap(index1, index2);
    }

    /** 
     * Replace object at index with another object.
     */
    void replaceObjectAtIndex(size_t index, T* object, bool releaseObject = true)
    {
        m_data.replace(index, object);
    }

    /** 
     * Revers the array
     */
    void reverseObjects()
    {
        m_data.reverse();
    }
    
    /* 
     * Shrinks the array so the memory footprint corresponds with the number of items
     */
    void reduceMemoryFootprint();
    {
        // N/A
    }
    
    /**
     */
    virtual BaseArray* clone() const
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

    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef std::vector<RCPtr<T>>::iterator iterator;
    typedef std::vector<RCPtr<T>>::const_iterator const_iterator;
    /**
     */
    iterator begin() { return data.begin(); }
    /**
     */
    iterator end() { return data.end(); }
    const_iterator cbegin() { return data.cbegin(); }
    /**
     */
    const_iterator cend() { return data.cend(); }
    
protected:
    std::vector<RCPtr<T>> m_data;

};

NS_YH_END

#endif // YH_COLLECTIONS_BASEARRAY_H_
