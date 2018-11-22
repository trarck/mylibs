#ifndef YH_PLIST_PLIST_H_
#define YH_PLIST_PLIST_H_

#include "../base/Ref.h"
#include "../collections/Value.h"
#include "PlistMacros.h"

NS_YH_PLIST_BEGIN

class PlistAscii:Ref
{
public:

	Value & read()
	{

	}



protected:
	Value _rootObject;
};


NS_YH_PLIST_END

#endif // YH_PLIST_PLIST2_H_
