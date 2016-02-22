#ifndef YH_YH_H_
#define YH_YH_H_

//base
#include "NSMacros.h"
#include "YHMacros.h"
#include "base/Internals.h"
#include "base/Object.h"
#include "base/RefPtr.h"

//platform
#include "platform/PlatformConfig.h"
#include "platform/PlatformDefine.h"
#include "platform/YHStdC.h"
#include "platform/Log.h"

//datastructure
#include "datastructure/LinkedList.h"

//jsoncpp
#include "jsoncpp/json.h"

//pugixml
#define PUGIXML_NO_EXCEPTIONS
#include "pugixml/pugixml.hpp"

//plist
#include "plist/Plist.h"

//io
#include "io/IOMacros.h"
#include "io/Buffer.h"
#include "io/InputStream.h"
#include "io/OutputStream.h"

//sp
#include "smartpointer/smart_ptr.h"

#endif //YH_YH_H_