#include "ObjectValue.h"

NS_YH_BEGIN

const ObjectValue ObjectValue::Null;

ObjectValue::ObjectValue()
:_type(NONE)
{
    
}

ObjectValue::ObjectValue(unsigned char v)
:_type(BYTE)
{
    _baseData.byteVal = v;
}

ObjectValue::ObjectValue(int v)
:_type(INTEGER)
{
    _baseData.intVal = v;
}

ObjectValue::ObjectValue(float v)
:_type(FLOAT)
{
    _baseData.floatVal = v;
}

ObjectValue::ObjectValue(double v)
:_type(DOUBLE)
{
    _baseData.doubleVal = v;
}

ObjectValue::ObjectValue(bool v)
:_type(BOOLEAN)
{
    _baseData.boolVal = v;
}

ObjectValue::ObjectValue(const char* v)
:_type(STRING)
{
    _baseData.strVal=new YHString(v);
}

ObjectValue::ObjectValue(const std::string& v)
:_type(STRING)
{
    _baseData.strVal=new YHString(v);
}

ObjectValue::ObjectValue(const ValueVector& v)
:_type(VECTOR)
{
    _baseData.vectorVal=new ValueVector();
    *(_baseData.vectorVal) = v;
}

ObjectValue::ObjectValue(const ValueMap& v)
:_type(MAP)
{
    _baseData.mapVal=new ValueMap();
    *(_baseData.mapVal) = v;
}

ObjectValue::ObjectValue(const ValueMapIntKey& v)
:_type(INT_KEY_MAP)
{
    _baseData.intKeyMapVal=new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
}

ObjectValue::ObjectValue(const ObjectValue& other)
{
    *this = other;
}

ObjectValue::~ObjectValue()
{
    clear();
}

ObjectValue& ObjectValue::operator= (const ObjectValue& other)
{
    if (this != &other) {
        switch (other._type) {
            case BYTE:
                _baseData.byteVal = other._baseData.byteVal;
                break;
            case INTEGER:
                _baseData.intVal = other._baseData.intVal;
                break;
            case FLOAT:
                _baseData.floatVal = other._baseData.floatVal;
                break;
            case DOUBLE:
                _baseData.doubleVal = other._baseData.doubleVal;
                break;
            case BOOLEAN:
                _baseData.boolVal = other._baseData.boolVal;
                break;
            case STRING:
                _baseData.strVal=other._baseData.strVal;
                _baseData.strVal->retain();
                break;
                
            case VECTOR:
                if (_baseData.vectorVal == NULL)
                    _baseData.vectorVal = new ValueVector();
                *(_baseData.vectorVal) = *(other._baseData.vectorVal);
                break;
            case MAP:
                if (_baseData.mapVal == NULL)
                    _baseData.mapVal = new ValueMap();
                *(_baseData.mapVal) = *(other._baseData.mapVal);
                break;
            case INT_KEY_MAP:
                if (_baseData.intKeyMapVal == NULL)
                    _baseData.intKeyMapVal = new ValueMapIntKey();
                *(_baseData.intKeyMapVal) = *(other._baseData.intKeyMapVal);
                break;

            default:
                break;
        }
        _type = other._type;
    }
    return *this;
}

ObjectValue& ObjectValue::operator= (unsigned char v)
{
    clear();
    _type = BYTE;
    _baseData.byteVal = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (int v)
{
    clear();
    _type = INTEGER;
    _baseData.intVal = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (float v)
{
    clear();
    _type = FLOAT;
    _baseData.floatVal = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (double v)
{
    clear();
    _type = DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (bool v)
{
    clear();
    _type = BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (const char* v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new YHString(v);
    return *this;
}

ObjectValue& ObjectValue::operator= (const std::string& v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new YHString(v);
    return *this;
}


ObjectValue& ObjectValue::operator= (const ValueVector& v)
{
    clear();
    _type = VECTOR;
    _baseData.vectorVal = new ValueVector();
    *(_baseData.vectorVal) = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (const ValueMap& v)
{
    clear();
    _type = MAP;
    _baseData.mapVal = new ValueMap();
    *(_baseData.mapVal) = v;
    return *this;
}

ObjectValue& ObjectValue::operator= (const ValueMapIntKey& v)
{
    clear();
    _type = INT_KEY_MAP;
    _baseData.intKeyMapVal = new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
    return *this;
}

///
unsigned char ObjectValue::asByte() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to byte");
    
    if (_type == BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == INTEGER)
    {
        return static_cast<unsigned char>(_baseData.intVal);
    }
    
    if (_type == STRING)
    {
        return static_cast<unsigned char>(_baseData.strVal->intValue());
    }
    
    if (_type == FLOAT)
    {
        return static_cast<unsigned char>(_baseData.floatVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<unsigned char>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
    }
    
    return 0;
}

int ObjectValue::asInt() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to int");
    
    if (_type == INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->intValue();
    }
    
    if (_type == FLOAT)
    {
        return static_cast<int>(_baseData.floatVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<int>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
    }
    
    return 0;
}

float ObjectValue::asFloat() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to float");
    
    if (_type == FLOAT)
    {
        return _baseData.floatVal;
    }
    
    if (_type == BYTE)
    {
        return static_cast<float>(_baseData.byteVal);
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->floatValue();
    }
    
    if (_type == INTEGER)
    {
        return static_cast<float>(_baseData.intVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<float>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1.0f : 0.0f;
    }
    
    return 0.0f;
}

double ObjectValue::asDouble() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to double");
    
    if (_type == DOUBLE)
    {
        return _baseData.doubleVal;
    }
    
    if (_type == BYTE)
    {
        return static_cast<double>(_baseData.byteVal);
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->doubleValue();
    }
    
    if (_type == INTEGER)
    {
        return static_cast<double>(_baseData.intVal);
    }
    
    if (_type == FLOAT)
    {
        return static_cast<double>(_baseData.floatVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1.0 : 0.0;
    }
    
    return 0.0;
}

bool ObjectValue::asBool() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to bool");
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    if (_type == BYTE)
    {
        return _baseData.byteVal == 0 ? false : true;
    }
    
    if (_type == STRING)
    {
        std::string val=_baseData.strVal->getCString();
        return (val == "0" || val == "false") ? false : true;
    }
    
    if (_type == INTEGER)
    {
        return _baseData.intVal == 0 ? false : true;
    }
    
    if (_type == FLOAT)
    {
        return _baseData.floatVal == 0.0f ? false : true;
    }
    
    if (_type == DOUBLE)
    {
        return _baseData.doubleVal == 0.0 ? false : true;
    }
    
    return true;
}

std::string ObjectValue::asString() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to string");
    
    if (_type == STRING)
    {
        return _baseData.strVal->getCString();
    }
    
    std::stringstream ret;
    
    switch (_type) {
        case BYTE:
            ret << _baseData.byteVal;
            break;
        case INTEGER:
            ret << _baseData.intVal;
            break;
        case FLOAT:
            ret << _baseData.floatVal;
            break;
        case DOUBLE:
            ret << _baseData.doubleVal;
            break;
        case BOOLEAN:
            ret << (_baseData.boolVal ? "true" : "false");
            break;
        default:
            break;
    }
    return ret.str();
}

ObjectValue::ValueVector& ObjectValue::asValueVector()
{
    YHASSERT(_type==VECTOR || _type==NONE, "ObjectValue::asValueVector _type is not vector");
    
	if (_type==NONE){
//		clear();
        _type=VECTOR;
        _baseData.vectorVal=new ValueVector();
    }
    
	return *(_baseData.vectorVal);
}

const ObjectValue::ValueVector& ObjectValue::asValueVector() const
{
    YHASSERT(_type==VECTOR || _type==NONE, "ObjectValue::asValueVector _type is not vector");
    
	static const ValueVector EMPTY_VALUEVECTOR;
	if (NONE == _type)
		return EMPTY_VALUEVECTOR;
	return *(_baseData.vectorVal);
}

ObjectValue::ValueMap& ObjectValue::asValueMap()
{
    YHASSERT(_type==MAP || _type==NONE, "ObjectValue::asValueVector _type is not map");
	if (NONE == _type){
        _type=MAP;
		_baseData.mapVal = new ValueMap();
    }
	return *(_baseData.mapVal);
}

const ObjectValue::ValueMap& ObjectValue::asValueMap() const
{
    YHASSERT(_type==MAP || _type==NONE, "ObjectValue::asValueVector _type is not map");
    
	static const ValueMap EMPTY_VALUEMAP;
	if (NONE == _type)
		return EMPTY_VALUEMAP;
	return *(_baseData.mapVal);
}

ObjectValue::ValueMapIntKey& ObjectValue::asIntKeyMap()
{
    YHASSERT(_type==INT_KEY_MAP || _type==NONE, "ObjectValue::asValueVector _type is not map");
    
	if (NONE == _type){
        _type=INT_KEY_MAP;
		_baseData.intKeyMapVal = new ValueMapIntKey();
    }
	return *(_baseData.intKeyMapVal);
}

const ObjectValue::ValueMapIntKey& ObjectValue::asIntKeyMap() const
{
	static const ValueMapIntKey EMPTY_VALUEMAP_INT_KEY;
	if (NONE == _type)
		return EMPTY_VALUEMAP_INT_KEY;
	return *(_baseData.intKeyMapVal);
}


static std::string getTabs(int depth)
{
    std::string tabWidth;
    
    for (int i = 0; i < depth; ++i)
    {
        tabWidth += "\t";
    }
    
    return tabWidth;
}

static std::string visit(const ObjectValue& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case ObjectValue::NONE:
        case ObjectValue::BYTE:
        case ObjectValue::INTEGER:
        case ObjectValue::FLOAT:
        case ObjectValue::DOUBLE:
        case ObjectValue::BOOLEAN:
        case ObjectValue::STRING:
            ret << v.asString() << "\n";
            break;
        default:
            YHASSERT(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string ObjectValue::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void ObjectValue::clear()
{
    
    switch (_type) {
        case STRING:
            _baseData.strVal->release();
            break;
        case VECTOR:
            YH_SAFE_DELETE(_baseData.vectorVal);
            break;
        case MAP:
            YH_SAFE_DELETE(_baseData.mapVal);
            break;
        case INT_KEY_MAP:
            YH_SAFE_DELETE(_baseData.intKeyMapVal);
            break;
        default:
            break;
    }
    
    _type = NONE;
    _baseData.doubleVal = 0.0;
}

NS_YH_END
