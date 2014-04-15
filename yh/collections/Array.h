#ifndef YH_COLLECTIONS_ARRAY_H_
#define YH_COLLECTIONS_ARRAY_H_

#include "../YHMacros.h"
#include "../base/Object.h"
#include "Vector.h"

NS_YH_BEGIN


#define YH_ARRAY_FOREACH(__array__, __object__)                  \
if (__array__) \
for( Array::iterator __it__ = (__array__)->begin();              \
__it__ != (__array__)->end() && ((__object__) = *__it__) != NULL;                     \
++__it__)


#define YH_ARRAY_FOREACH_REVERSE(__array__, __object__)          \
if (__array__) \
for( Array::iterator __it__ = (__array__)->rbegin();             \
__it__ != (__array__)->rend() && ((__object__) = *__it__) != NULL;                        \
++__it__ )

/**
 * 可变数组
 * 直接使用Object做为Vector的对象，如果要取得具体内容，使用类型转换。
 * 不推荐使用，推荐使用Vector
 */
class Array : public Object
{
public:
//    /**
//     * @brief Creates an empty array.s
//     */
//    static Array* create();
//    /** 
//     * @brief Create an array with objects 
//     */
//    static Array* create(Object* object, ...);
//    /**
//     * @brief Create an array with one object 
//     */
//    static Array* createWithObject(Object* object);
//    /** 
//     * @brief Create an array with a default capacity 
//     */
//    static Array* createWithCapacity(int capacity);
//    /** Create an array with from an existing array 
//     */
//    static Array* createWithArray(Array* otherArray)
//    {
//        return otherArray->clone();
//    }
//    
//    /**
//     @brief   Generate a Array pointer by file
//     @param   pFileName  The file name of *.plist file
//     @return  The Array pointer generated from the file
//     */
//    static Array* createWithContentsOfFile(const std::string& pFileName);
//    
//    /*
//     *@brief The same meaning as arrayWithContentsOfFile(), but it doesn't call autorelease, so the
//     * invoker should call release().
//     */
//    static Array* createWithContentsOfFileThreadSafe(const std::string& pFileName);

    Array();
    
    /**
     */
    ~Array();

    /** 
     * @brief Initializes an array
     */
    bool init();
    /** 
     @brief Initializes an array with one object
     */
    bool initWithObject(Object* object);
    /** 
     @brief Initializes an array with some objects
     */
    bool initWithObjects(Object* object, ...);
    /** 
     @brief Initializes an array with capacity
     */
    bool initWithCapacity(int capacity);
    /** 
     @breif Initializes an array with an existing array
     */
    bool initWithArray(Array* otherArray);

    /** 
     @brief Returns element count of the array
     */
    size_t count() const
    {
        return m_data.size();
    }
    
    /** 
     @return Returns capacity of the array
     */
    size_t capacity() const
    {
        return m_data.capacity();
    }
    /** 
     @return Returns index of a certain object, return UINT_MAX if doesn't contain the object
     */
    int getIndexOfObject(Object* object) const;

    /** 
     @return Returns an element with a certain index
     */
    Object* getObjectAtIndex(int index)
    {
        YHASSERT(index>=0 && index < count(), "index out of range in getObjectAtIndex()");
        return m_data.at(index);
    }

    /** 
     @return Returns the last element of the array
     */
    Object* getLastObject()
    {
        return m_data.back();
    }

    /** 
     @return Returns a random element
     */
    Object* getRandomObject();

    /** 
     @return Returns a Boolean value that indicates whether object is present in array.
     */
    bool containsObject(Object* object) const;

    bool isEqualToArray(Array* otherArray);
    
    
    // Adding Objects

    /** 
     @brief Add a certain object
     */
    void addObject(Object* object);

    /** 
     @brief Add all elements of an existing array
     */
    void addObjectsFromArray(Array* otherArray);
    /** 
     @brief Insert a certain object at a certain index
     */
    void insertObject(Object* object, int index);
    /** 
     @brief sets a certain object at a certain index
     */
    void setObject(Object* object, int index);
    /** 
     @brief sets a certain object at a certain index without retaining. Use it with caution
     */
    void fastSetObject(Object* object, int index)
    {
        setObject(object, index);
    }

    // Removing Objects

    /** 
     @brief Remove last object
     */
    void removeLastObject(bool releaseObj = true);
    /** 
     @brief Remove a certain object
     */
    void removeObject(Object* object, bool releaseObj = true);
    /** 
     @brief Remove an element with a certain index
     */
    void removeObjectAtIndex(size_t index, bool releaseObj = true);
    /** 
     @brief Remove all elements
     */
    void removeObjectsInArray(Array* otherArray);
    /** 
     @brief Remove all objects
     */
    void removeAllObjects();
    /** 
     @brief Fast way to remove a certain object
     */
    void fastRemoveObject(Object* object);
    /** 
     * Fast way to remove an element with a certain index
     */
    void fastRemoveObjectAtIndex(int index);

    // Rearranging Content

    /** 
     Swap two elements
     */
    void exchangeObject(Object* object1, Object* object2);
    /** 
     * Swap two elements with certain indexes
     */
    void exchangeObjectAtIndex(size_t index1, size_t index2);

    /** 
     * Replace object at index with another object.
     */
    void replaceObjectAtIndex(int index, Object* object, bool releaseObject = true);

    /** 
     * Revers the array
     */
    void reverseObjects();
    /* 
     * Shrinks the array so the memory footprint corresponds with the number of items
     */
    void reduceMemoryFootprint();
  
    /**
     */
    virtual Array* clone() const;

    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef Vector<Object*>::iterator iterator;
    typedef Vector<Object*>::const_iterator const_iterator;
    
    /**
     */
    iterator begin() { return m_data.begin(); }
    /**
     */
    iterator end() { return m_data.end(); }
    
    inline const Vector<Object*>& getData() const
    {
        return m_data;
    }
    
protected:
    Vector<Object*> m_data;

};

NS_YH_END

#endif // YH_COLLECTIONS_ARRAY_H_
