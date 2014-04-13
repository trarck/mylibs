#ifndef YH_COLLECTIONS_ARRAY_H_
#define YH_COLLECTIONS_ARRAY_H_

#include "../YHMacros.h"
#include "../base/Object.h"
#include "Vector.h"

NS_YH_BEGIN

template<class T>
class Array : public Object
{
public:
    /** 
     * @brief Creates an empty array.s
     */
    static Array* create();
    /** 
     * @brief Create an array with objects 
     */
    static Array* create(Object* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /**
     * @brief Create an array with one object 
     */
    static Array* createWithObject(Object* object);
    /** 
     * @brief Create an array with a default capacity 
     */
    static Array* createWithCapacity(ssize_t capacity);
    /** Create an array with from an existing array 
     */
    static Array* createWithArray(Array* otherArray);
    /**
     @brief   Generate a Array pointer by file
     @param   pFileName  The file name of *.plist file
     @return  The Array pointer generated from the file
     */
    static Array* createWithContentsOfFile(const std::string& pFileName);
    
    /*
     @brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
     invoker should call release().
     */
    static Array* createWithContentsOfFileThreadSafe(const std::string& pFileName);

    /**
     */
    ~Array();

    /** Initializes an array 
     */
    bool init();
    /** Initializes an array with one object 
     */
    bool initWithObject(Object* object);
    /** Initializes an array with some objects 
     */
    bool initWithObjects(Object* object, ...) CC_REQUIRES_NULL_TERMINATION;
    /** Initializes an array with capacity 
     */
    bool initWithCapacity(ssize_t capacity);
    /** Initializes an array with an existing array 
     */
    bool initWithArray(Array* otherArray);

    // Querying an Array

    /** Returns element count of the array 
     */
    ssize_t count() const
    {
        return data.size();
    }
    /** Returns capacity of the array 
     */
    ssize_t capacity() const
    {
        return data.capacity();
    }
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object 
     */
    ssize_t getIndexOfObject(Object* object) const;
    /**
     */

    /** Returns an element with a certain index 
     */
    Object* getObjectAtIndex(ssize_t index)
    {
        CCASSERT(index>=0 && index < count(), "index out of range in getObjectAtIndex()");
        return data[index].get();
    }

    /** Returns the last element of the array 
     */
    Object* getLastObject()
    {
        return data.back().get();
    }

    /** Returns a random element 
     * @js NA
     * @lua NA
     */
    Object* getRandomObject();

    /** Returns a Boolean value that indicates whether object is present in array. 
     * @js NA
     */
    bool containsObject(Object* object) const;
    /** @since 1.1 
     * @js NA
     */
    bool isEqualToArray(Array* otherArray);
    // Adding Objects

    /** Add a certain object 
     * @js NA
     */
    void addObject(Object* object);
    /**
     * @js NA
     */
    /** Add all elements of an existing array 
     * @js NA
     */
    void addObjectsFromArray(Array* otherArray);
    /** Insert a certain object at a certain index 
     * @js NA
     */
    void insertObject(Object* object, ssize_t index);
    /** sets a certain object at a certain index 
     * @js NA
     * @lua NA
     */
    void setObject(Object* object, ssize_t index);
    /** sets a certain object at a certain index without retaining. Use it with caution 
     * @js NA
     * @lua NA
     */
    void fastSetObject(Object* object, ssize_t index)
    {
        setObject(object, index);
    }

    // Removing Objects

    /** Remove last object 
     * @js NA
     */
    void removeLastObject(bool releaseObj = true);
    /** Remove a certain object 
     * @js NA
     */
    void removeObject(Object* object, bool releaseObj = true);
    /** Remove an element with a certain index 
     * @js NA
     */
    void removeObjectAtIndex(ssize_t index, bool releaseObj = true);
    /** Remove all elements 
     * @js NA
     */
    void removeObjectsInArray(Array* otherArray);
    /** Remove all objects 
     * @js NA
     */
    void removeAllObjects();
    /** Fast way to remove a certain object 
     * @js NA
     */
    void fastRemoveObject(Object* object);
    /** Fast way to remove an element with a certain index 
     * @js NA
     */
    void fastRemoveObjectAtIndex(ssize_t index);

    // Rearranging Content

    /** Swap two elements 
     * @js NA
     */
    void exchangeObject(Object* object1, Object* object2);
    /** Swap two elements with certain indexes 
     * @js NA
     */
    void exchangeObjectAtIndex(ssize_t index1, ssize_t index2);

    /** Replace object at index with another object. 
     * @js NA
     */
    void replaceObjectAtIndex(ssize_t index, Object* object, bool releaseObject = true);

    /** Revers the array 
     * @js NA
     */
    void reverseObjects();
    /* Shrinks the array so the memory footprint corresponds with the number of items 
     * @js NA
     */
    void reduceMemoryFootprint();
  
    /* override functions 
     * @js NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     * @js NA
     * @lua NA
     */
    virtual Array* clone() const;

    // ------------------------------------------
    // Iterators
    // ------------------------------------------
#if CC_USE_ARRAY_VECTOR
    typedef std::vector<RCPtr<Object>>::iterator iterator;
    typedef std::vector<RCPtr<Object>>::const_iterator const_iterator;
    /**
     * @js NA
     * @lua NA
     */
    iterator begin() { return data.begin(); }
    /**
     * @js NA
     * @lua NA
     */
    iterator end() { return data.end(); }
    const_iterator cbegin() { return data.cbegin(); }
    /**
     * @js NA
     * @lua NA
     */
    const_iterator cend() { return data.cend(); }

    std::vector<RCPtr<Object>> data;

#else
    /**
     * @js NA
     * @lua NA
     */
    Object** begin() { return &data->arr[0]; }
    /**
     * @js NA
     * @lua NA
     */
    Object** end() { return &data->arr[data->num]; }

    ccArray* data;

#endif

//protected:
    /**
     * @js NA
     * @lua NA
     */
    Array();
};

// end of data_structure group
/// @}

NS_YH_END

#endif // YH_COLLECTIONS_ARRAY_H_
