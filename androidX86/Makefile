make_and_install:   all	install_C

install:    all install_C 
all:
#	ndk-build.cmd V=1
	ndk-build.cmd
	adb push libs/x86/scrcapx86 /data/local/tmp/scrcapx86
	adb shell chmod 777 /data/local/tmp/scrcapx86
	
	adb push libs/x86/tracerx86 /data/local/tmp/tracerx86
	adb shell chmod 777 /data/local/tmp/tracerx86
clean:
	@rm -rf obj libs


install_C:
	adb push libs/x86/tracerx86 /data/local/tmp/tracerx86
	adb shell chmod 777 /data/local/tmp/tracerx86
	
	adb push libs/x86/upgrade /data/local/tmp/upgradex86
	adb shell chmod 777 /data/local/tmp/upgradex86
