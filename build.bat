rem win
gyp --depth=. -Dyh_library=static_library --generator-output=build/win32

rem ios
gyp --depth=. -Dyh_library=static_library -f xcode -DOS=ios --generator-output=build/ios

rem mac
gyp --depth=. -Dyh_library=static_library -f xcode -DOS=mac --generator-output=build/mac

rem android
gyp --depth=. -Dyh_library=static_library -f android -DOS=android -Gandroid_top_dir=./

rem cmake
build\gyp\gyp --depth=. -Dyh_library=static_library -f cmake-android -DOS=android -Gandroid_top_dir=./  --generator-output=build\cmake

rem window下测试
python gyp_yh.py --depth=. -Dyh_library=static_library -Dtarget_arch=x86 --generator-output=build/window