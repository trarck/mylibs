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
            platform/Log.cpp
          ],
          'conditions': [
              [ 'OS=="win"', {
                  'defines': [
                    '_WIN32_WINNT=0x0600',
                    '_GNU_SOURCE',
                  ],
                  'sources': [
                    platform/win32/StdC-win32.cpp
                  ]
                }
             ]
         ]
      }
  ]
}