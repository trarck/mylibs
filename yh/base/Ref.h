#ifndef YH_BASE_REF_H_
#define YH_BASE_REF_H_

#include "../YHMacros.h"

NS_YH_BEGIN


/** Interface that defines how to clone an object */
class Clonable
{
public:
	/** returns a copy of the object */
    virtual Clonable* clone() const = 0;
    /**
     * @js NA
     * @lua NA
     */
	virtual ~Clonable() {};
};

/**
 * 引用计数基类
 * 注意和RefCount不能同时使用
 */
class Ref
{
public:
    /**
     * Constructor
     *
     * The object's reference count is 1 after construction.
     * @js NA
     */
    Ref();
    
    /**
     * @js NA
     * @lua NA
     */
    virtual ~Ref();
    
    /**
     * Release the ownership immediately.
     *
     * This decrements the object's reference count.
     *
     * If the reference count reaches 0 after the descrement, this object is
     * destructed.
     *
     * @see retain, autorelease
     * @js NA
     */
    void release();

    /**
     * Retains the ownership.
     *
     * This increases the object's reference count.
     *
     * @see release, autorelease
     * @js NA
     */
    inline void retain()
    {
        ++_referenceCount;
    }

    unsigned int getReferenceCount() const;

    /**
     * Returns a boolean value that indicates whether this object and a given
     * object are equal.
     *
     * @param object    The object to be compared to this object.
     *
     * @returns True if this object and @p object are equal, otherwise false.
     * @js NA
     * @lua NA
     */
    virtual bool isEqual(const Ref* object);

public:
	
	inline void setId(unsigned int id)
	{
	    _id = id;
	}

	inline unsigned int getId()
	{
	    return _id;
	}
	
protected:
    /// object id
    unsigned int _id;
    /// count of references
    unsigned int _referenceCount;
};

NS_YH_END

#endif // YH_BASE_REF_H_
