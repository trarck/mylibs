rem win
gyp --depth=. -Dlibrary=static_library --generator-output=build/win32

rem ios
gyp --depth=. -Dlibrary=static_library -f xcode -DOS=ios --generator-output=build/ios

rem ios
gyp --depth=. -Dlibrary=static_library -f xcode -DOS=mac --generator-output=build/mac