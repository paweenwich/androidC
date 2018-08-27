TOLUA=jni/luac/tolua.exe

make_and_install:   all	install_C

install:    all install_C install_shell install_data install_script
all:	lua
#	ndk-build.cmd V=1 
	ndk-build.cmd

clean:
	@rm -rf obj libs


install_C:
	adb push libs/armeabi/hello /data/local/tmp/helloarm
	adb shell chmod 777 /data/local/tmp/helloarm

	adb push libs/armeabi/upgrade /data/local/tmp/upgrade
	adb shell chmod 777 /data/local/tmp/upgrade

	
	adb push libs/armeabi/libarmhlpx86.so /data/local/tmp/libarmhlparm.so
	adb shell chmod 777 /data/local/tmp/libarmhlparm.so
	
	cp libs/armeabi/libarmhlpx86.so /cygdrive/d/kwang/Unity/UnityHelper/Assets/Plugins/Android/libarmhlparm.so	

	adb push libs/armeabi/libloader.so /data/local/tmp/libloader.so
	adb shell chmod 777 /data/local/tmp/libloader.so
	adb push libs/armeabi/testloader /data/local/tmp/testloader
	adb shell chmod 777 /data/local/tmp/testloader

	

	
#install_fwt:
#	adb push libs/x86/FantasyWarTactic.dll /data/local/tmp/FantasyWarTactic.dll
	

install_shell:
	adb push shell/load.sh /data/local/tmp/load.sh
	adb shell chmod 777 /data/local/tmp/load.sh
	adb push shell/map.sh /data/local/tmp/map.sh
	adb shell chmod 777 /data/local/tmp/map.sh
	adb push shell/task.sh /data/local/tmp/task.sh
	adb shell chmod 777 /data/local/tmp/task.sh
	adb push shell/traceall.sh /data/local/tmp/traceall.sh
	adb shell chmod 777 /data/local/tmp/traceall.sh

	
install_data:
	adb push shell/libc_orig.offset /data/local/tmp/libc_orig.offset
	adb shell chmod 777 /data/local/tmp/libc_orig.offset	

install_script:
	adb push shell/Bot.lua /data/local/tmp/Bot.lua
	adb push shell/cscript.lua /data/local/tmp/cscript.lua
	adb push shell/upgrade.lua /data/local/tmp/upgrade.lua

lua:	jni/hello/lua_hello.cpp \
	jni/loader/lua_server.cpp \
	jni/upgrade/lua_upgrade.cpp

jni/hello/lua_hello.cpp:   jni/hello/lua_hello.luapkg
	$(TOLUA) -n lua_hello -o jni/hello/lua_hello.cpp -H jni/hello/lua_hello.hpp jni/hello/lua_hello.luapkg

jni/loader/lua_server.cpp:   jni/loader/lua_server.luapkg
	$(TOLUA) -n lua_server -o jni/loader/lua_server.cpp -H jni/loader/lua_server.hpp jni/loader/lua_server.luapkg

jni/upgrade/lua_upgrade.cpp:   jni/upgrade/lua_upgrade.luapkg
	$(TOLUA) -n lua_upgrade -o jni/upgrade/lua_upgrade.cpp -H jni/upgrade/lua_upgrade.hpp jni/upgrade/lua_upgrade.luapkg