#include "Value.h"

NS_YH_BEGIN

const Value Value::Null;

Value::Value()
:_type(NONE)
{
    
}

Value::Value(unsigned char v)
:_type(BYTE)
{
    _baseData.byteVal = v;
}

Value::Value(int v)
:_type(INTEGER)
{
    _baseData.intVal = v;
}

Value::Value(int64_t v)
	: _type(LONG)
{
	_baseData.longVal = v;
}

Value::Value(float v)
:_type(FLOAT)
{
    _baseData.floatVal = v;
}

Value::Value(double v)
:_type(DOUBLE)
{
    _baseData.doubleVal = v;
}

Value::Value(bool v)
:_type(BOOLEAN)
{
    _baseData.boolVal = v;
}

Value::Value(const char* v)
:_type(STRING)
{
    _baseData.strVal=new YHString(v);
}

Value::Value(const std::string& v)
:_type(STRING)
{
    _baseData.strVal=new YHString(v);
}

Value::Value(const ValueVector& v)
:_type(VECTOR)
{
    _baseData.vectorVal=new ValueVector();
    *(_baseData.vectorVal) = v;
}

Value::Value(const ValueMap& v)
:_type(MAP)
{
    _baseData.mapVal=new ValueMap();
    *(_baseData.mapVal) = v;
}

Value::Value(const ValueMapIntKey& v)
:_type(INT_KEY_MAP)
{
    _baseData.intKeyMapVal=new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
}

Value::Value(const Value& other)
{
    *this = other;
}

Value::~Value()
{
    clear();
}

Value& Value::operator= (const Value& other)
{
    if (this != &other) 
	{
        switch (other._type) 
		{
            case BYTE:
                _baseData.byteVal = other._baseData.byteVal;
                break;
            case INTEGER:
                _baseData.intVal = other._baseData.intVal;
                break;
			case LONG:
				_baseData.longVal = other._baseData.longVal;
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

Value& Value::operator= (unsigned char v)
{
    clear();
    _type = BYTE;
    _baseData.byteVal = v;
    return *this;
}

Value& Value::operator= (int v)
{
    clear();
    _type = INTEGER;
    _baseData.intVal = v;
    return *this;
}

Value& Value::operator= (int64_t v)
{
	clear();
	_type = LONG;
	_baseData.longVal = v;
	return *this;
}

Value& Value::operator= (float v)
{
    clear();
    _type = FLOAT;
    _baseData.floatVal = v;
    return *this;
}

Value& Value::operator= (double v)
{
    clear();
    _type = DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

Value& Value::operator= (bool v)
{
    clear();
    _type = BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

Value& Value::operator= (const char* v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new YHString(v);
    return *this;
}

Value& Value::operator= (const std::string& v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new YHString(v);
    return *this;
}


Value& Value::operator= (const ValueVector& v)
{
    clear();
    _type = VECTOR;
    _baseData.vectorVal = new ValueVector();
    *(_baseData.vectorVal) = v;
    return *this;
}

Value& Value::operator= (const ValueMap& v)
{
    clear();
    _type = MAP;
    _baseData.mapVal = new ValueMap();
    *(_baseData.mapVal) = v;
    return *this;
}

Value& Value::operator= (const ValueMapIntKey& v)
{
    clear();
    _type = INT_KEY_MAP;
    _baseData.intKeyMapVal = new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
    return *this;
}

///
unsigned char Value::asByte() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to byte");
    
	unsigned char ret = 0;

	switch (_type) 
	{
		case BYTE:
			ret= _baseData.byteVal;
			break;
		case INTEGER:
			ret= static_cast<unsigned char>(_baseData.intVal);
			break;
		case LONG:
			ret= static_cast<unsigned char>(_baseData.longVal);
			break;
		case FLOAT:
			ret= static_cast<unsigned char>(_baseData.floatVal);
			break;
		case DOUBLE:
			ret= static_cast<unsigned char>(_baseData.doubleVal);
			break;
		case BOOLEAN:
			ret= _baseData.boolVal ? 1 : 0;
			break;
		case STRING:
			ret= static_cast<unsigned char>(_baseData.strVal->intValue());
			break;
	}

    
    return ret;
}

int Value::asInt() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to int");
	int ret = 0;

	switch (_type) 
	{
		case BYTE:
			ret = _baseData.byteVal;
			break;
		case INTEGER:
			ret =_baseData.intVal;
			break;
		case LONG:
			ret = _baseData.longVal;
			break;
		case FLOAT:
			ret = static_cast<int>(_baseData.floatVal);
			break;
		case DOUBLE:
			ret = static_cast<int>(_baseData.doubleVal);
			break;
		case BOOLEAN:
			ret = _baseData.boolVal ? 1 : 0;
			break;
		case STRING:
			ret = _baseData.strVal->intValue();
			break;
	}
    
    return ret;
}


int64_t Value::asLong() const
{
	YHASSERT(_type != VECTOR && _type != MAP && _type != INT_KEY_MAP, "can't covert from vector or map to int");
	int64_t ret = 0;

	switch (_type)
	{
		case BYTE:
			ret = _baseData.byteVal;
			break;
		case INTEGER:
			ret = _baseData.intVal;
			break;
		case LONG:
			ret = _baseData.longVal;
			break;
		case FLOAT:
			ret = static_cast<int64_t>(_baseData.floatVal);
			break;
		case DOUBLE:
			ret = static_cast<int64_t>(_baseData.doubleVal);
			break;
		case BOOLEAN:
			ret = _baseData.boolVal ? 1 : 0;
			break;
		case STRING:
			ret = _baseData.strVal->longValue();
			break;
	}

	return ret;
}

float Value::asFloat() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to float");
    
	float ret = 0.0f;

	switch (_type) 
	{
		case BYTE:
			ret = static_cast<float>(_baseData.byteVal);
			break;
		case INTEGER:
			ret = static_cast<float>(_baseData.intVal);
			break;
		case LONG:
			ret = static_cast<float>(_baseData.longVal);
			break;
		case FLOAT:
			ret = _baseData.floatVal;
			break;
		case DOUBLE:
			ret = static_cast<float>(_baseData.doubleVal);
			break;
		case BOOLEAN:
			ret = _baseData.boolVal ? 1.0f : 0.0f;
			break;
		case STRING:
			ret = _baseData.strVal->floatValue();
			break;
	}

	return ret;

}

double Value::asDouble() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to double");
    

	double ret = 0.0f;

	switch (_type)
	{
		case BYTE:
			ret = static_cast<double>(_baseData.byteVal);
			break;
		case INTEGER:
			ret = static_cast<double>(_baseData.intVal);
			break;
		case LONG:
			ret = static_cast<double>(_baseData.longVal);
			break;
		case FLOAT:
			ret = _baseData.floatVal;
			break;
		case DOUBLE:
			ret = _baseData.doubleVal;
			break;
		case BOOLEAN:
			ret = _baseData.boolVal ? 1.0f : 0.0f;
			break;
		case STRING:
			ret = _baseData.strVal->doubleValue();
			break;
	}

	return ret;
}

bool Value::asBool() const
{
    YHASSERT(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to bool");

	bool ret = false;

	switch (_type)
	{
		case BYTE:
			ret = _baseData.byteVal ? true : false;
			break;
		case INTEGER:
			ret = _baseData.intVal ? true : false;
			break;
		case LONG:
			ret = _baseData.longVal ? true : false;
			break;
		case FLOAT:
			ret = _baseData.floatVal==0?false:true;
			break;
		case DOUBLE:
			ret = _baseData.doubleVal == 0 ? false : true;
			break;
		case BOOLEAN:
			ret = _baseData.boolVal;
			break;
		case STRING:
			std::string val = _baseData.strVal->getCString();
			ret= (val == "0" || val == "false") ? false : true;
			break;
	}

	return ret;
}

std::string Value::asString() const
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
		case LONG:
			ret << _baseData.longVal;
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

Value::ValueVector& Value::asValueVector()
{
    YHASSERT(_type==VECTOR || _type==NONE, "Value::asValueVector _type is not vector");
    
	if (_type==NONE){
//		clear();
        _type=VECTOR;
        _baseData.vectorVal=new ValueVector();
    }
    
	return *(_baseData.vectorVal);
}

const Value::ValueVector& Value::asValueVector() const
{
    YHASSERT(_type==VECTOR || _type==NONE, "Value::asValueVector _type is not vector");
    
	static const ValueVector EMPTY_VALUEVECTOR;
	if (NONE == _type)
		return EMPTY_VALUEVECTOR;
	return *(_baseData.vectorVal);
}

Value::ValueMap& Value::asValueMap()
{
    YHASSERT(_type==MAP || _type==NONE, "Value::asValueVector _type is not map");
	if (NONE == _type){
        _type=MAP;
		_baseData.mapVal = new ValueMap();
    }
	return *(_baseData.mapVal);
}

const Value::ValueMap& Value::asValueMap() const
{
    YHASSERT(_type==MAP || _type==NONE, "Value::asValueVector _type is not map");
    
	static const ValueMap EMPTY_VALUEMAP;
	if (NONE == _type)
		return EMPTY_VALUEMAP;
	return *(_baseData.mapVal);
}

Value::ValueMapIntKey& Value::asIntKeyMap()
{
    YHASSERT(_type==INT_KEY_MAP || _type==NONE, "Value::asValueVector _type is not map");
    
	if (NONE == _type){
        _type=INT_KEY_MAP;
		_baseData.intKeyMapVal = new ValueMapIntKey();
    }
	return *(_baseData.intKeyMapVal);
}

const Value::ValueMapIntKey& Value::asIntKeyMap() const
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

static std::string visit(const Value& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case Value::NONE:
        case Value::BYTE:
        case Value::INTEGER:
        case Value::FLOAT:
        case Value::DOUBLE:
        case Value::BOOLEAN:
        case Value::STRING:
            ret << v.asString() << "\n";
            break;
        default:
            YHASSERT(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string Value::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void Value::clear()
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
