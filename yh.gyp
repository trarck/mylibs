{
  'target_defaults': {
    'conditions': [
      ['OS != "win"', {
        'defines': [
          '_LARGEFILE_SOURCE',
          '_FILE_OFFSET_BITS=64',
        ],
        'conditions': [
          ['OS=="solaris"', {
            'cflags': [ '-pthreads' ],
          }],
          ['OS not in "solaris android"', {
            'cflags': [ '-pthread' ],
          }],
        ],
      }],
    ],
    'xcode_settings': {
      'WARNING_CFLAGS': [ '-Wall', '-Wextra', '-Wno-unused-parameter' ],
      'OTHER_CFLAGS': [ '-g', '--std=gnu89', '-pedantic' ],
    }
  },

  'targets': [
      {
          'target_name': 'libyh',
          'type': '<(library)',
          'include_dirs': [
            'yh/',
          ],
          'sources': [
            'yh/yh.h',
            'yh/NSMacros.h',
            'yh/YHMacros.h',
            './yh/base/Internals.h',
            './yh/base/Object.cpp',
            './yh/base/Object.h',
            './yh/base/RCPtr.h',
            './yh/base/RefCount.cpp',
            './yh/base/RefCount.h',
            './yh/base/RefPtr.cpp',
            './yh/base/RefPtr.h',
            './yh/collections/Array.cpp',
            './yh/collections/Array.h',
            './yh/collections/BaseArray.h',
            './yh/collections/BaseDictionary.h',
            './yh/collections/Dictionary.cpp',
            './yh/collections/Dictionary.h',
            './yh/collections/Map.h',
            './yh/collections/ObjectValue.cpp',
            './yh/collections/ObjectValue.h',
            './yh/collections/SimpleValue.cpp',
            './yh/collections/SimpleValue.h',
            './yh/collections/Vector.h',
            './yh/datastructure/DataStructureMacros.h',
            './yh/datastructure/Iterator-implement.h',
            './yh/datastructure/Iterator.h',
            './yh/datastructure/LinkedList-implement.h',
            './yh/datastructure/LinkedList.h',
            './yh/io/Buffer.cpp',
            './yh/io/Buffer.h',
            './yh/io/IeeeHalfPrecision.cpp',
            './yh/io/IeeeHalfPrecision.h',
            './yh/io/InputStream.cpp',
            './yh/io/InputStream.h',
            './yh/io/IOMacros.h',
            './yh/io/OutputStream.cpp',
            './yh/io/OutputStream.h',
            './yh/jsoncpp/autolink.h',
            './yh/jsoncpp/config.h',
            './yh/jsoncpp/features.h',
            './yh/jsoncpp/forwards.h',
            './yh/jsoncpp/json.h',
            './yh/jsoncpp/json_batchallocator.h',
            './yh/jsoncpp/json_internalarray.inl',
            './yh/jsoncpp/json_internalmap.inl',
            './yh/jsoncpp/json_macros.h',
            './yh/jsoncpp/json_reader.cpp',
            './yh/jsoncpp/json_value.cpp',
            './yh/jsoncpp/json_valueiterator.inl',
            './yh/jsoncpp/json_writer.cpp',
            './yh/jsoncpp/reader.h',
            './yh/jsoncpp/value.h',
            './yh/jsoncpp/writer.h',
            './yh/platform/Log.cpp',
            './yh/platform/Log.h',
            './yh/platform/nullptr.h',
            './yh/platform/PlatformConfig.h',
            './yh/platform/PlatformDefine.h',
            './yh/platform/PlatformMacros.h',
            './yh/platform/YHStdC.h',
            './yh/plist/Plist.cpp',
            './yh/plist/Plist.h',
            './yh/plist/Plist2.cpp',
            './yh/plist/Plist2.h',
            './yh/pugixml/pugiconfig.hpp',
            './yh/pugixml/pugixml.cpp',
            './yh/pugixml/pugixml.hpp',
            './yh/shell/OptionParser.cpp',
            './yh/shell/OptionParser.h',
            './yh/smartpointer/shared_ptr.h',
            './yh/smartpointer/SmartPointerMacros.h',
            './yh/smartpointer/smart_ptr.h',
            './yh/smartpointer/smart_ptr_inherit.h',
            './yh/sqlite/Column.cpp',
            './yh/sqlite/Column.h',
            './yh/sqlite/SqliteDriver.cpp',
            './yh/sqlite/SqliteDriver.h',
            './yh/sqlite/SqliteMacros.h',
            './yh/sqlite/Statement.cpp',
            './yh/sqlite/Statement.h',
            './yh/sqlite/Transaction.cpp',
            './yh/sqlite/Transaction.h',
            './yh/string/utf8/checked.h',
            './yh/string/utf8/core.h',
            './yh/string/utf8/unchecked.h',
            './yh/string/utf8.h',
            './yh/string/YHString.cpp',
            './yh/string/YHString.h',
          ],
          'conditions': [
              ['OS=="win"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/win32/compat/stdint.h',
                    './yh/platform/win32/PlatformDefine-win32.h',
                    './yh/platform/win32/StdC-win32.cpp',
                    './yh/platform/win32/StdC-win32.h',
                    './yh/platform/win32/Win32StdC.h',
                  ]
                }
             ],
             ['OS=="mac"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/mac/PlatformDefine-mac.h',
                    './yh/platform/mac/StdC-mac.h',
                  ]
                }
             ],

             ['OS=="ios"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/ios/PlatformDefine-ios.h',
                    './yh/platform/ios/StdC-ios.h',
                  ]
                }
             ],
             ['OS=="android"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/android/PlatformDefine-android.h',
                    './yh/platform/android/StdC-android.h',
                  ]
                }
             ],
             ['OS=="linux"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/linux/PlatformDefine-linux.h',
                    './yh/platform/linux/StdC-linux.h',
                  ]
                }
             ],
             ['OS=="winrt"', {
                  'defines': [

                  ],
                  'sources': [
                    './yh/platform/winrt/PlatformDefine-winrt.h',
                    './yh/platform/winrt/StdC-winrt.cpp',
                    './yh/platform/winrt/StdC-winrt.h',
                  ]
                }
             ]
         ]
      }
  ]
}