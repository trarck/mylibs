#ifndef YH_COLLECTIONS_VALUE_H_
#define YH_COLLECTIONS_VALUE_H_

#include "../YHMacros.h"
#include "../base/Ref.h"
#include "../string/YHString.h"
#include "Vector.h"
#include "Map.h"

NS_YH_BEGIN


#define VALUE_CREATE(type)\
static Value* create(type v)\
{\
Value* value=new Value(v);\
if (value) {\
return value;\
}\
return NULL;\
}

class Value:public Ref
{
public:
    static const Value Null;
    
    typedef Vector<Value*> ValueVector;
    typedef Map<std::string,Value*> 	  ValueMap;
    typedef Map<int,Value*> 	  ValueMapIntKey;
    
    Value();
    
    explicit Value(unsigned char v);
    explicit Value(int v);
	explicit Value(int64_t v);
    explicit Value(float v);
    explicit Value(double v);
    explicit Value(bool v);
    explicit Value(const char* v);
    explicit Value(const std::string& v);
    
    explicit Value(const ValueVector& v);
    
    explicit Value(const ValueMap& v);
    
    explicit Value(const ValueMapIntKey& v);
    
    Value(const Value& other);

    ~Value();
    
    // assignment operator
    Value& operator= (const Value& other);
    
    Value& operator= (unsigned char v);
    Value& operator= (int v);
	Value& operator= (int64_t v);
    Value& operator= (float v);
    Value& operator= (double v);
    Value& operator= (bool v);
    Value& operator= (const char* v);
    Value& operator= (const std::string& v);
    
    Value& operator= (const ValueVector& v);
    
    Value& operator= (const ValueMap& v);
    
    Value& operator= (const ValueMapIntKey& v);
    
    unsigned char asByte() const;
    int asInt() const;
	int64_t asLong() const;
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
		LONG,
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
    
    static Value* create()
    {
        Value* value=new Value();
        if (value) {
//            cocosValue->autorelease();
            return value;
        }
        return NULL;
    }
    
	VALUE_CREATE(unsigned char);
    VALUE_CREATE(int);
	VALUE_CREATE(int64_t);
    VALUE_CREATE(float);
    VALUE_CREATE(double);
    VALUE_CREATE(bool);
    VALUE_CREATE(const char*);
    VALUE_CREATE(const std::string&);

	VALUE_CREATE(const ValueVector&);
	VALUE_CREATE(const ValueMap&);
	VALUE_CREATE(const ValueMapIntKey&);
    
private:
    
    void clear();
    
    union
    {
        unsigned char byteVal;
        int intVal;
		int64_t longVal;
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


#endif //YH_COLLECTIONS_VALUE_H_
