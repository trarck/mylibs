#ifndef YH_JSONCPP_FORWARDS_H_
# define YH_JSONCPP_FORWARDS_H_

#include "json_macros.h"
# include "config.h"

NS_YH_BEGIN
	
namespace Json {

   // writer.h
   class FastWriter;
   class StyledWriter;

   // reader.h
   class Reader;

   // features.h
   class Features;

   // value.h
   typedef int Int;
   typedef unsigned int UInt;
   class StaticString;
   class Path;
   class PathArgument;
   class Value;
   class ValueIteratorBase;
   class ValueIterator;
   class ValueConstIterator;
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   class ValueAllocator;
   class ValueMapAllocator;
   class ValueInternalLink;
   class ValueInternalArray;
   class ValueInternalMap;
#endif // #ifdef JSON_VALUE_USE_INTERNAL_MAP

} // namespace Json

NS_YH_END
	
#endif // JSON_FORWARDS_H_INCLUDED
