cd /d %~dp0%


cmake ^
 -G "MinGW Makefiles" ^
 -DCMAKE_MAKE_PROGRAM="E:\android-ndk-r10d\prebuilt\windows-x86_64\bin\make.exe" ^
 -DCMAKE_TOOLCHAIN_FILE=android.toolchain.cmake ^
 -DANDROID_NDK="E:\android-ndk-r10d" ^
 -DCMAKE_BUILD_TYPE=Release ^
 -DANDROID_ABI="armeabi-v7a" ^
 -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.8 ^
 -DANDROID_STL="gnustl_static" ^
 -DANDROID_NATIVE_API_LEVEL=16 ^
 .
cmake --build .
