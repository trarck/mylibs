{
  'variables': { 
    'with_json': 'false',
    'with_xml': 'false',
    'with_shell': 'false',
    'with_sqlite': 'false'
  },
  
  'targets': [
      {
          'target_name': 'libyh',
          'type': '<(yh_library)',
          
          'defines':[

          ],

          'include_dirs': [
            'yh/',
          ],
          'sources': [
            'yh/yh.h',
            'yh/NSMacros.h',
            'yh/YHMacros.h',
            './yh/base/Ref.cpp',
            './yh/base/Ref.h',
            './yh/base/RCPtr.h',
            './yh/base/RefPtr.cpp',
            './yh/base/RefPtr.h',
            './yh/collections/Map.h',
            './yh/collections/ObjectValue.cpp',
            './yh/collections/ObjectValue.h',
            './yh/collections/Vector.h',
            './yh/datastructure/DataStructureMacros.h',
            './yh/datastructure/Iterator-implement.h',
            './yh/datastructure/Iterator.h',
            './yh/datastructure/LinkedList-implement.h',
            './yh/datastructure/LinkedList.h',
            './yh/io/IOMacros.h',
            './yh/io/Buffer.cpp',
            './yh/io/Buffer.h',
            './yh/io/IeeeHalfPrecision.cpp',
            './yh/io/IeeeHalfPrecision.h',
            './yh/io/Stream.cpp',
            './yh/io/Stream.h',            
            './yh/io/BufferStream.cpp',
            './yh/io/BufferStream.h',
            './yh/io/MemoryStream.cpp',
            './yh/io/MemoryStream.h',
            './yh/io/BinaryWriter.cpp',
            './yh/io/BinaryWriter.h',
            './yh/io/BinaryReader.cpp',
            './yh/io/BinaryReader.h',
            './yh/io/RingBuffer.cpp',
            './yh/io/RingBuffer.h',
            './yh/platform/Internals.h',
            './yh/platform/Log.cpp',
            './yh/platform/Log.h',
            './yh/platform/nullptr.h',
            './yh/platform/PlatformConfig.h',
            './yh/platform/PlatformDefine.h',
            './yh/platform/PlatformMacros.h',
            './yh/platform/YHStdC.h',
            './yh/string/utf8/checked.h',
            './yh/string/utf8/core.h',
            './yh/string/utf8/unchecked.h',
            './yh/string/utf8.h',
            './yh/string/YHString.cpp',
            './yh/string/YHString.h',            
          ],
          'conditions': [
             ['with_json=="true"',{
                  'defines':[
                    'YH_USE_JSON'
                  ],
                  'sources': [
                    './yh/jsoncpp/autolink.h',
                    './yh/jsoncpp/config.h',
                    './yh/jsoncpp/features.h',
                    './yh/jsoncpp/forwards.h',
                    './yh/jsoncpp/json.h',
                    './yh/jsoncpp/json_batchallocator.h',
                    './yh/jsoncpp/json_macros.h',
                    './yh/jsoncpp/json_reader.cpp',
                    './yh/jsoncpp/json_value.cpp',
                    './yh/jsoncpp/json_writer.cpp',
                    './yh/jsoncpp/reader.h',
                    './yh/jsoncpp/value.h',
                    './yh/jsoncpp/writer.h',
                  ]
                }
             ],
             
             ['with_xml=="true"',{
                  'defines':[
                    'YH_USE_XML'
                  ],
                  'sources': [
                    './yh/plist/Plist.cpp',
                    './yh/plist/Plist.h',
                    './yh/pugixml/pugiconfig.hpp',
                    './yh/pugixml/pugixml.cpp',
                    './yh/pugixml/pugixml.hpp',
                  ]
                }
             ],
             
             ['with_shell=="true"',{
                  'defines':[
                    'YH_USE_SHELL'
                  ],
                  'sources': [
                      './yh/shell/OptionParser.cpp',
                      './yh/shell/OptionParser.h',
                  ]
                }
             ],
             
            ['with_sqlite=="true"',{
                  'defines':[
                    'YH_USE_SQLITE','SQLITE_HAS_CODEC',
                  ],
                  'sources': [
                        './yh/securesqlite3/sqlite3secure.c',
                        './yh/sqlite/Column.cpp',
                        './yh/sqlite/Column.h',
                        './yh/sqlite/SqliteDriver.cpp',
                        './yh/sqlite/SqliteDriver.h',
                        './yh/sqlite/SqliteMacros.h',
                        './yh/sqlite/Statement.cpp',
                        './yh/sqlite/Statement.h',
                        './yh/sqlite/Transaction.cpp',
                        './yh/sqlite/Transaction.h',
                  ]
                }
             ],
             
             ['OS=="win"', {
                  'defines': [
                    'WIN32','_WINDOWS'
                  ],
                  'sources': [
                    './yh/platform/win32/compat/stdint.h',
                    './yh/platform/win32/PlatformDefine-win32.h',
                    './yh/platform/win32/StdC-win32.cpp',
                    './yh/platform/win32/StdC-win32.h',
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
             ],
             ['yh_library=="static_library"',{
                  'defines':['YH_STATIC'],
                }
             ],
             ['yh_library=="shared_library"',{
                  'defines':['YH_USRDLL'],                  
                }
             ],
             #['OS=="win" and yh_library=="shared_library"', {
             #     'defines': [
             #       'SQLITE_API=__declspec(dllexport)'
             #     ]
             #   }
             #]
         ],
         'configurations': {
            'Debug': {
                'defines': [ 'YH_USE_SCRIPT_LOG','YH_DEBUG'],
            },
			'Release': {
                'defines': ['NODEBUG'],
            }
         },
      },
      
      {
          'dependencies': ['libyh'],
          'target_name': 'testyh',
          'type': 'executable',
          'include_dirs': [
            './',
            './deps/gtest/include'
          ],
          'sources': [
            './tests/gtest_main.cc',
            './tests/ds/list_unittest.cpp',
            './tests/io/buffer_unittest.cpp',
            './tests/io/bufferstream_unittest.cpp',
            './tests/io/memorystream_unittest.cpp',
            './tests/io/ringbuffer_unittest.cpp',
          ],
          'conditions': [
             ['OS=="win"', {
                  'defines': [
                    'WIN32','_WINDOWS'
                  ],
                  'library_dirs': [
                    './deps/gtest/libraries/windows/x86/Debug',
                  ],
                  'link_settings': {
                    'libraries': [
                      '-lgtestd.lib',
                    ],
                  },
                }
             ],
          ]
    }
  ]
}