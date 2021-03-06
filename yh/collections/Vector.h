#ifndef YH_COLLECTIONS_VECTOR_H_
#define YH_COLLECTIONS_VECTOR_H_

#include <vector>
#include <functional>
#include <algorithm> // for std::find
#include "../YHMacros.h"

NS_YH_BEGIN


/**
 * 对标准的std::vector时行封装。实现变长数组。
 * 内容必须为Obejct或其子类
 * 通常使用值的方式传递。如果为了性能，可用RefPtr包装一个Vector的指针对象。
 */
template<class T>
class Vector
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
    typedef typename std::vector<T>::iterator iterator;
    typedef typename std::vector<T>::const_iterator const_iterator;
    
    typedef typename std::vector<T>::reverse_iterator reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
    
    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
//    const_iterator cbegin() const { return _data.cbegin(); }
//    const_iterator cend() const { return _data.cend(); }
    
    reverse_iterator rbegin() { return _data.rbegin(); }
    const_reverse_iterator rbegin() const { return _data.rbegin(); }
    
    reverse_iterator rend() { return _data.rend(); }
    const_reverse_iterator rend() const { return _data.rend(); }
    
//    const_reverse_iterator crbegin() const { return _data.crbegin(); }
//    const_reverse_iterator crend() const { return _data.crend(); }
    
    /** Constructor */
    Vector<T>()
    : _data()
    {

    }
    
    /** Constructor with a capacity */
    explicit Vector<T>(size_t capacity)
    : _data()
    {
        reserve(capacity);
    }

    /** Destructor */
    ~Vector<T>()
    {
        YHDEBUG("In the destructor of Vector.");
        clear();
    }

    /** Copy constructor */
    Vector<T>(const Vector<T>& other)
    {
        _data = other._data;
        addRefForAllObjects();
    }
    
//    /** Move constructor */
//    Vector<T>(Vector<T>&& other)
//    {
//        _data = std::move(other._data);
//    }
    
    /** Copy assignment operator */
    Vector<T>& operator=(const Vector<T>& other)
    {
        if (this != &other) {
//            YHDEBUG("In the copy assignment operator!");
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    
//    /** Move assignment operator */
//    Vector<T>& operator=(Vector<T>&& other)
//    {
//        if (this != &other) {
////            YHDEBUG("In the move assignment operator!");
//            clear();
//            _data = std::move(other._data);
//        }
//        return *this;
//    }
    
// Don't uses operator since we could not decide whether it needs 'retain'/'release'.
//    T& operator[](int index)
//    {
//        return _data[index];
//    }
//    
//    const T& operator[](int index) const
//    {
//        return _data[index];
//    }
    
    /** @brief Request a change in capacity 
     *  @param capacity Minimum capacity for the vector.
     *         If n is greater than the current vector capacity, 
     *         the function causes the container to reallocate its storage increasing its capacity to n (or greater).
     */
    void reserve(size_t n)
    {
        _data.reserve(n);
    }
    
    /** @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
     *  @note This capacity is not necessarily equal to the vector size. 
     *        It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
     *  @return The size of the currently allocated storage capacity in the vector, measured in terms of the number elements it can hold.
     */
    size_t capacity() const
    {
        return _data.capacity();
    }
    
    /** @brief Returns the number of elements in the vector.
     *  @note This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
     *  @return The number of elements in the container.
     */
    size_t size() const
    {
        return  _data.size();
    }
    
    /** @brief Returns whether the vector is empty (i.e. whether its size is 0).
     *  @note This function does not modify the container in any way. To clear the content of a vector, see Vector<T>::clear.
     */
    bool empty() const
    {
        return _data.empty();
    }
    
    /** Returns the maximum number of elements that the vector can hold. */
    size_t max_size() const
    {
        return _data.max_size();
    }
    
    /** Returns index of a certain object, return UINT_MAX if doesn't contain the object */
    size_t getIndex(T object) const
    {
        const_iterator iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            return iter - _data.begin();

        return -1;
    }

    /** @brief Find the object in the vector.
     *  @return Returns an iterator to the first element in the range [first,last) that compares equal to val. 
     *          If no such element is found, the function returns last.
     */
    const_iterator find(T object) const
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    iterator find(T object)
    {
        return std::find(_data.begin(), _data.end(), object);
    }
    
    /** Returns the element at position 'index' in the vector. */
    T at(size_t index) const
    {
        YHASSERT( index >= 0 && index < size(), "index out of range in getObjectAtIndex()");
        return _data[index];
    }

    /** Returns the first element in the vector. */
    T front() const
    {
        return _data.front();
    }
    
    /** Returns the last element of the vector. */
    T back() const
    {
        return _data.back();
    }

    /** Returns a random element of the vector. */
    T getRandomObject() const
    {
        if (!_data.empty())
        {
            size_t randIdx = rand() % _data.size();
            return *(_data.begin() + randIdx);
        }
        return NULL;
    }

    /** Returns a Boolean value that indicates whether object is present in vector. */
    bool contains(T object) const
    {
        return( std::find(_data.begin(), _data.end(), object) != _data.end() );
    }

    /** Returns true if the two vectors are equal */
    bool equals(const Vector<T> &other)
    {
        size_t s = this->size();
        if (s != other.size())
            return false;
        
        for (size_t i = 0; i < s; i++)
        {
            if (!this->at(i)->isEqual(other.at(i)))
            {
                return false;
            }
        }
        return true;
    }

    // Adds objects
    
    /** @brief Adds a new element at the end of the vector, after its current last element.
     *  @note This effectively increases the container size by one,
     *        which causes an automatic reallocation of the allocated storage space 
     *        if -and only if- the new vector size surpasses the current vector capacity.
     */
    void pushBack(T object)
    {
        YHASSERT(object != NULL, "The object should not be NULL");
        _data.push_back( object );
        object->retain();
    }
    
    /** Push all elements of an existing vector to the end of current vector. */
    void pushBack(const Vector<T>& other)
    {
        for(iterator iter=other.begin();iter!=other.end;++iter) {
            _data.push_back((*iter));
            (*iter)->retain();
        }
    }

    /** @brief Insert a certain object at a certain index 
     *  @note The vector is extended by inserting new elements before the element at the specified 'index',
     *        effectively increasing the container size by the number of elements inserted.
     *        This causes an automatic reallocation of the allocated storage space 
     *        if -and only if- the new vector size surpasses the current vector capacity.
     */
    void insert(size_t index, T object)
    {
        YHASSERT(index >= 0 && index <= size(), "Invalid index!");
        YHASSERT(object != NULL, "The object should not be NULL");
        _data.insert((_data.begin() + index), object);
        object->retain();
    }
    
    void insert(size_t position, iterator begin,iterator end)
    {
        _data.insert(position, begin,end);
        //add reatain
        for(iterator iter=begin;iter!=end;++iter){
            iter->retain();
        }
    }
    
    // Removes Objects

    /** Removes the last element in the vector, 
     *  effectively reducing the container size by one, decrease the referece count of the deleted object.
     */
    void popBack()
    {
        YHASSERT(!_data.empty(), "no objects added");
        T last = _data.back();
        _data.pop_back();
        last->release();
    }
    
    /** @brief Remove a certain object.
     *  @param object The object to be removed.
     *  @param toRelease Whether to decrease the referece count of the deleted object.
     */
    void eraseObject(T object, bool toRelease = true)
    {
        YHASSERT(object != NULL, "The object should not be NULL");
        iterator iter = std::find(_data.begin(), _data.end(), object);
        if (iter != _data.end())
            _data.erase(iter);
        if (toRelease)
            object->release();
    }

    /** @brief Removes from the vector with an iterator. 
     *  @param position Iterator pointing to a single element to be removed from the vector.
     *  @return An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     */
    iterator erase(iterator position)
    {
        YHASSERT(position >= _data.begin() && position < _data.end(), "Invalid position!");
        (*position)->release();
        return _data.erase(position);
    }
    
    /** @brief Removes from the vector with a range of elements (  [first, last)  ).
     *  @param first The beginning of the range
     *  @param last The end of the range, the 'last' will not used, it's only for indicating the end of range.
     *  @return An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     */
    iterator erase(iterator first, iterator last)
    {
        for (iterator iter = first; iter != last; ++iter)
        {
            (*iter)->release();
        }
        
        return _data.erase(first, last);
    }
    
    /** @brief Removes from the vector with an index.
     *  @param index The index of the element to be removed from the vector.
     *  @return An iterator pointing to the new location of the element that followed the last element erased by the function call.
     *          This is the container end if the operation erased the last element in the sequence.
     */
    iterator erase(size_t index)
    {
        YHASSERT(!_data.empty() && index >=0 && index < size(), "Invalid index!");
        iterator it = _data.begin()+index;
        (*it)->release();
        return _data.erase(it);
    }

    /** @brief Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
     *  @note All the elements in the vector will be released (referece count will be decreased).
     */
    void clear()
    {
        for( iterator it = _data.begin(); it != _data.end(); ++it ) {
            (*it)->release();
        }
        _data.clear();
    }

    // Rearranging Content

    /** Swap two elements */
    void swap(T object1, T object2)
    {
        //TODO check c++11
        
        size_t idx1 = getIndex(object1);
        size_t idx2 = getIndex(object2);

        swap(idx1, idx2);
//        std::swap( _data[idx1], _data[idx2] );
    }
    
    /** Swap two elements with certain indexes */
    void swap(size_t index1, size_t index2)
    {
        YHASSERT(index1 >=0 && index1 < size() && index2 >= 0 && index2 < size(), "Invalid indices");

        T temp=_data[index1];
        _data[index1]=_data[index2];
        _data[index2]=temp;
        
//        std::swap( _data[index1], _data[index2] );
    }

    /** Replace object at index with another object. */
    void replace(size_t index, T object)
    {
        YHASSERT(index >= 0 && index < size(), "Invalid index!");
        YHASSERT(object != NULL, "The object should not be NULL");
        
        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    /** reverses the vector */
    void reverse()
    {
        std::reverse( _data.begin(), _data.end());
    }
    
    /** Shrinks the vector so the memory footprint corresponds with the number of items */
    void shrinkToFit()
    {
        _data.shrink_to_fit();
    }
    
protected:
    
    /** Retains all the objects in the vector */
    void addRefForAllObjects()
    {
        for(iterator iter=_data.begin();iter!=_data.end();++iter) {
            (*iter)->retain();
        }
    }
    
    std::vector<T> _data;
};

// end of data_structure group
/// @}

NS_YH_END

#endif // YH_COLLECTIONS_VECTOR_H_
