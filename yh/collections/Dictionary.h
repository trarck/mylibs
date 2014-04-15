#ifndef YH_COLLECTIONS_DICTIONARY_H_
#define YH_COLLECTIONS_DICTIONARY_H_

#include "../YHMacros.h"
#include "Map.h"
#include "../base/Object.h"


NS_YH_BEGIN

/**
 * 字典
 * 直接使用Object做为Vector的对象，如果要取得具体内容，使用类型转换。
 * 不推荐使用，推荐使用Map
 * 还没有完全实现
 */
class Dictionary : public Object
{
public:
    /**
     * The constructor of Dictionary.
     */
    Dictionary();
    
    /**
     * The destructor of Dictionary
     * @js NA
     * @lua NA
     */
    ~Dictionary();
    
    /** Initializes the dictionary. It returns true if the initializations was successful.
     */
    bool init();
    /**
     *  Get the count of elements in Dictionary.
     *
     *  @return  The count of elements.
     */
    unsigned int count();
    
    /**
     *  Return all keys of elements.
     *
     *  @return  The array contains all keys of elements. It's an autorelease object yet.
     */
    Array* allKeys();
    
    /**
     *  Get all keys according to the specified object.
     *  @warning  We use '==' to compare two objects
     *  @return   The array contains all keys for the specified object. It's an autorelease object yet.
     */
    Array* allKeysForObject(Object* object);
    
    /**
     *  Get the object according to the specified string key.
     *
     *  @note The dictionary needs to use string as key. If integer is passed, an assert will appear.
     *  @param key  The string key for searching.
     *  @return The object matches the key. You need to force convert it to the type you know.
     *  @code
     *     // Assume that the elements are String* pointers. Convert it by following code.
     *     String* pStr = static_cast<String*>(pDict->objectForKey("key1"));
     *     // Do something about pStr.
     *     // If you don't know the object type, properly you need to use dynamic_cast<SomeType*> to check it.
     *     String* pStr2 = dynamic_cast<String*>(pDict->objectForKey("key1"));
     *     if (pStr2 != NULL) {
     *          // Do something about pStr2
     *     }
     *  @endcode
     *  @see objectForKey(intptr_t)
     * @js NA
     */
    Object* objectForKey(const std::string& key);
    
    /**
     *  Get the object according to the specified integer key.
     *
     *  @note The dictionary needs to use integer as key. If string is passed, an assert will appear.
     *  @param key  The integer key for searching.
     *  @return The object matches the key.
     *  @see objectForKey(const std::string&)
     * @js NA
     */
    Object* objectForKey(intptr_t key);
    
    /** Get the value according to the specified string key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are __String pointer.
     *  @param key  The string key for searching
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't __String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(const std::string& key);
    
    /** Get the value according to the specified integer key.
     *
     *  @note Be careful to use this function since it assumes the objects in the dictionary are __String pointer.
     *  @param key  The string key for searching.
     *  @return An instance of String.
     *          It will return an empty string if the objects aren't __String pointer or the key wasn't found.
     *  @see valueForKey(intptr_t)
     *  @js NA
     */
    const __String* valueForKey(intptr_t key);
    
    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Whe the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Object*, intptr_t)
     * @js NA
     */
    void setObject(Object* pObject, const std::string& key);
    
    /** Insert an object to dictionary, and match it with the specified string key.
     *
     *  @note Then the first time this method is invoked, the key type will be set to string.
     *        After that you can't setObject with an integer key.
     *        If the dictionary contains the key you passed, the object matching the key will be released and removed from dictionary.
     *        Then the new object will be inserted after that.
     *  @param pObject  The Object to be inserted.
     *  @param key      The string key for searching.
     *  @see setObject(Object*, const std::string&)
     *  @js NA
     */
    void setObject(Object* pObject, intptr_t key);
    
    /**
     *  Remove an object by the specified string key.
     *
     *  @param key  The string key for searching.
     *  @see removeObjectForKey(intptr_t), removeObjectsForKeys(Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(const std::string& key);
    
    /**
     *  Remove an object by the specified integer key.
     *
     *  @param key  The integer key for searching.
     *  @see removeObjectForKey(const std::string&), removeObjectsForKeys(Array*),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectForKey(intptr_t key);
    
    /**
     *  Remove objects by an array of keys.
     *
     *  @param pKeyArray  The array contains keys to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectForElememt(DictElement*), removeAllObjects().
     *  @js NA
     */
    void removeObjectsForKeys(Array* pKey__Array);
    
    /**
     *  Remove an object by an element.
     *
     *  @param pElement  The element need to be removed.
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(Array*), removeAllObjects().
     * @js NA
     * @lua NA
     */
    void removeObjectForElememt(DictElement* pElement);
    
    /**
     *  Remove all objects in the dictionary.
     *
     *  @see removeObjectForKey(const std::string&), removeObjectForKey(intptr_t),
     *       removeObjectsForKeys(Array*), removeObjectForElememt(DictElement*).
     * @js NA
     */
    void removeAllObjects();
    
    /**
     *  Return a random object in the dictionary.
     *
     *  @return The random object.
     *  @see objectForKey(intptr_t), objectForKey(const std::string&)
     *  @js NA
     *  @lua NA
     */
    Object* randomObject();
    
    /**
     *  Create a dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see createWithDictionary(Dictionary*), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static Dictionary* create();
    
    /**
     *  Create a dictionary with an existing dictionary.
     *
     *  @param srcDict The exist dictionary.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithContentsOfFile(const char*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static Dictionary* createWithDictionary(Dictionary* srcDict);
    
    /**
     *  Create a dictionary with a plist file.
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which is an autorelease object.
     *  @see create(), createWithDictionary(Dictionary*), createWithContentsOfFileThreadSafe(const char*).
     *  @js NA
     */
    static Dictionary* createWithContentsOfFile(const char *pFileName);
    
    /**
     *  Write a dictionary to a plist file.
     *  @param fullPath The full path of the plist file. You can get writeable path by getWritablePath()
     *  @return true if successed, false if failed
     *  @js NA
     *  @lua NA
     */
    bool writeToFile(const char *fullPath);
    
    /**
     *  Create a dictionary with a plist file.
     *
     *  @note the return object isn't an autorelease object.
     *        This can make sure not using autorelease pool in a new thread.
     *        Therefore, you need to manage the lifecycle of the return object.
     *        It means that when you don't need it, CC_SAFE_RELEASE needs to be invoked.
     *
     *  @param  pFileName  The name of the plist file.
     *  @return A dictionary which isn't an autorelease object.
     *  @js NA
     *  @lua NA
     */
    static Dictionary* createWithContentsOfFileThreadSafe(const char *pFileName);
    
    /* override functions
     *  @js NA
     *  @lua NA
     */
    virtual void acceptVisitor(DataVisitor &visitor);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual Dictionary* clone() const;
    
private:
    /**
     *  For internal usage, invoked by setObject.
     */
    void setObjectUnSafe(Object* pObject, const std::string& key);
    void setObjectUnSafe(Object* pObject, const intptr_t key);
    
public:
    /**
     *  All the elements in dictionary.
     *
     *  @note For internal usage, we need to declare this member variable as public since it's used in UT_HASH.
     */
    DictElement* _elements;
private:
    
    /** The support type of dictionary, it's confirmed when setObject is invoked. */
    enum DictType
    {
        kDictUnknown = 0,
        kDictStr,
        kDictInt
    };
    
    /**
     *  The type of dictionary, it's assigned to kDictUnknown by default.
     */
    DictType _dictType;
};

NS_YH_END

#endif // YH_COLLECTIONS_DICTIONARY_H_
