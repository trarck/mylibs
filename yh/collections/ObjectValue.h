#ifndef YH_COLLECTIONS_OBJECT_VALUE_H_
#define YH_COLLECTIONS_OBJECT_VALUE_H_

#include "../YHMacros.h"
#include "../base/Ref.h"
#include "../string/YHString.h"
#include "Vector.h"
#include "Map.h"

NS_YH_BEGIN


#define OBJECT_VALUE_CREATE(type)\
static ObjectValue* create(type v)\
{\
ObjectValue* value=new ObjectValue(v);\
if (value) {\
return value;\
}\
return NULL;\
}

class ObjectValue:public Ref
{
public:
    static const ObjectValue Null;
    
    typedef Vector<ObjectValue*> ValueVector;
    typedef Map<std::string,ObjectValue*> 	  ValueMap;
    typedef Map<int,ObjectValue*> 	  ValueMapIntKey;
    
    ObjectValue();
    
    explicit ObjectValue(unsigned char v);
    explicit ObjectValue(int v);
    explicit ObjectValue(float v);
    explicit ObjectValue(double v);
    explicit ObjectValue(bool v);
    explicit ObjectValue(const char* v);
    explicit ObjectValue(const std::string& v);
    
    explicit ObjectValue(const ValueVector& v);
    
    explicit ObjectValue(const ValueMap& v);
    
    explicit ObjectValue(const ValueMapIntKey& v);
    
    ObjectValue(const ObjectValue& other);
    ~ObjectValue();
    
    // assignment operator
    ObjectValue& operator= (const ObjectValue& other);
    
    ObjectValue& operator= (unsigned char v);
    ObjectValue& operator= (int v);
    ObjectValue& operator= (float v);
    ObjectValue& operator= (double v);
    ObjectValue& operator= (bool v);
    ObjectValue& operator= (const char* v);
    ObjectValue& operator= (const std::string& v);
    
    ObjectValue& operator= (const ValueVector& v);
    
    ObjectValue& operator= (const ValueMap& v);
    
    ObjectValue& operator= (const ValueMapIntKey& v);
    
    unsigned char asByte() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;

    ValueVector& asValueVector();
    const ValueVector& asValueVector() const;
    
    ValueMap& asValueMap();
    const ValueMap& asValueMap() const;
    
    ValueMapIntKey& asIntKeyMap();
    const ValueMapIntKey& asIntKeyMap() const;
    
    enum Type
    {
        NONE,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
		VECTOR,
		MAP,
		INT_KEY_MAP
    };
    
    inline bool isNull() const { return _type == NONE; }

    inline Type getType() const { return _type; };
    
    std::string getDescription();
    
    static ObjectValue* create()
    {
        ObjectValue* value=new ObjectValue();
        if (value) {
//            cocosValue->autorelease();
            return value;
        }
        return NULL;
    }
    
    OBJECT_VALUE_CREATE(unsigned char);
    OBJECT_VALUE_CREATE(int);
    OBJECT_VALUE_CREATE(float);
    OBJECT_VALUE_CREATE(double);
    OBJECT_VALUE_CREATE(bool);
    OBJECT_VALUE_CREATE(const char*);
    OBJECT_VALUE_CREATE(const std::string&);
    
private:
    
    void clear();
    
    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
        YHString* strVal;
		ValueVector* vectorVal;
		ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
        
    } _baseData;

    Type _type;
};

NS_YH_END


#endif /* defined(YH_COLLECTIONS_OBJECT_VALUE_H_) */
