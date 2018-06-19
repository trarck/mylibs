#ifndef YH_YH_H_
#define YH_YH_H_

//base
#include "NSMacros.h"
#include "YHMacros.h"
#include "base/Ref.h"
#include "base/RefPtr.h"

//platform
#include "platform/PlatformConfig.h"
#include "platform/PlatformDefine.h"
#include "platform/YHStdC.h"
#include "platform/Log.h"
#include "platform/Internals.h"

//datastructure
#include "datastructure/LinkedList.h"

//jsoncpp
#if defined(YH_USE_JSON)
#include "jsoncpp/json.h"
#endif

#if defined(YH_USE_XML)
//pugixml
#include "pugixml/pugixml.hpp"

//plist
#include "plist/Plist.h"
#endif

//io
#include "io/IOMacros.h"
#include "io/Buffer.h"
#include "io/RingBuffer.h"
#include "io/Stream.h"
#include "io/MemoryStream.h"
#include "io/BufferStream.h"
#include "io/BinaryReader.h"
#include "io/BinaryWriter.h"

//sp
#if defined(YH_USE_SP)
#include "smartpointer/smart_ptr.h"
#endif

#if defined(YH_USE_SQLITE)
//sqlite3 c
#include "securesqlite3/sqlite3.h"

//Sqlite Class
#include "sqlite/Column.h"
#include "sqlite/Statement.h"
#include "sqlite/Transaction.h"
#include "sqlite/SqliteDriver.h"
#endif

#endif //YH_YH_H_