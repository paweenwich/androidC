CC_ARM=/usr/bin/arm-linux-gnueabi-g++-4.7
OPTIONS_ARM  = -v -Wl,--hash-style=sysv -fpermissive -static 
NDK_INCLUDE = /media/linux/android-ndk-r12b/platforms/android-19/arch-arm/usr/include
arm:
	$(CC_ARM) $(OPTIONS_ARM) tracer.cpp -o /tmp/tracer_arm 


LINKER= /system/bin/linker

CC=D:/android-ndk-r12b/toolchains/arm-linux-androideabi-4.9/prebuilt/windows-x86_64/bin/arm-linux-androideabi-g++
#OPTIONS= --sysroot=D:/android-ndk-r12b/platforms/android-9/arch-arm	#OK /system/lib/arm/libm_orig.so,/system/lib/arm/linker
#OPTIONS= --sysroot=D:/android-ndk-r12b/platforms/android-19/arch-arm	#OK /system/lib/arm/libm_orig.so,/system/lib/arm/linker
#OPTIONS= --sysroot=D:/android-ndk-r12b/platforms/android-22/arch-arm	#OK /system/lib/arm/libm_orig.so,/system/lib/arm/linker
OPTIONS= --sysroot=D:/android-ndk-r12b/platforms/android-19/arch-arm	#OK /system/lib/arm/libm_orig.so,/system/lib/arm/linker
OPTIONS += -ID:/android-ndk-r12b/sources/cxx-stl/stlport/stlport -ID:/android-ndk-r12b/build/sources/cxx-stl/gabi++/include
#OPTIONS += -Wl,-dynamic-linker=$(LINKER) 
#OPTIONS += -fpic -ffunction-sections -funwind-tables -fstack-protector-strong -no-canonical-prefixes  
#OPTIONS += -g -march=armv5te -mtune=xscale -msoft-float  -mthumb -Os -DNDEBUG  -Ijni/traceme -DANDROID 
#OPTIONS += -isystem D:/android-ndk-r12b/platforms/android-24/arch-arm/usr/include
STATIC = D:/android-ndk-r12b/sources/cxx-stl/stlport/libs/armeabi/libstlport_static.a
all:	out install
	
#   -fPIE -pie	    build but fail to run

out:
#	$(CC) $(OPTIONS) -nostdlib -lc -o traceme traceme.c
#	$(CC) $(OPTIONS) -static -v -o traceme traceme.c
	$(CC) $(OPTIONS) -static-libgcc -v -o tracer tracer.cpp hook.cpp $(STATIC) -llog
	
install:
	adb push tracer /data/local/tmp/tracer
	adb shell chmod 777 /data/local/tmp/tracer


