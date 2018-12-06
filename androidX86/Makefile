make_and_install:   all	install_C

install:    all install_C 
all:
#	ndk-build.cmd V=1
	ndk-build.cmd
	adb push libs/x86/scrcapx86 /data/local/tmp/scrcapx86
	adb shell chmod 777 /data/local/tmp/scrcapx86
	
	adb push libs/x86/tracerx86 /data/local/tmp/tracerx86
	adb shell chmod 777 /data/local/tmp/tracerx86

	adb push libs/x86/libloader.so /data/local/tmp/libloader.so

clean:
	@rm -rf obj libs


install_C:
	adb push libs/x86/tracerx86 /data/local/tmp/tracerx86
	adb shell chmod 777 /data/local/tmp/tracerx86
	
	adb push libs/x86/upgrade /data/local/tmp/upgradex86
	adb shell chmod 777 /data/local/tmp/upgradex86

lua:
	ndk-build.cmd
	adb push libs/x86/lua /data/local/tmp/lua
	adb shell chmod 777 /data/local/tmp/lua

	adb push libs/x86/luac /data/local/tmp/luac
	adb shell chmod 777 /data/local/tmp/luac
	
	adb push libs/x86/tolua /data/local/tmp/tolua
	adb shell chmod 777 /data/local/tmp/tolua
	
	adb push libs/x86/toluapp /data/local/tmp/toluapp
	adb shell chmod 777 /data/local/tmp/toluapp
