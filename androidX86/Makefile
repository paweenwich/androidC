make_and_install:   all	install_C

install:    all install_C 
all:	jni/luaServer/lua_server.cpp ragnarok ragnarokMono elf mtail rom
#	ndk-build.cmd V=1
	ndk-build.cmd
	adb push libs/x86/scrcapx86 /data/local/tmp/scrcapx86
	adb shell chmod 777 /data/local/tmp/scrcapx86
	
	adb push libs/x86/tracerx86 /data/local/tmp/tracerx86
	adb shell chmod 777 /data/local/tmp/tracerx86

	adb push libs/x86/libloader.so /data/local/tmp/libloader.so
	adb push libs/x86/libtestso.so /data/local/tmp/libtestso.so
#	adb push libs/x86/elf /data/local/tmp/elf
#	adb shell chmod 777 /data/local/tmp/elf
	adb push jni/tracer/install.sh /data/local/tmp/install.sh
	adb shell chmod 777 /data/local/tmp/install.sh

rom:	
	adb push script/rom/AScript_FrameWork_GUI_view_MainView.lua /data/local/tmp/script
	adb push script/rom/AScript_Refactory_Game_FunctionSystem_Logic_AI_Myself_AI_CMD_Myself_Skill.lua /data/local/tmp/script
	adb push script/rom/AScript_Refactory_Game_FunctionSystem_Logic_AI_Myself_AI_Myself.lua /data/local/tmp/script
	adb push script/rom/AScript_FrameWork_GUI_view_MainSubviews_MiniMapWindow.lua /data/local/tmp/script
	adb push script/rom/AScript_FrameWork_GUI_view_MainView.lua /data/local/tmp/script
#	oop for test
	adb push script/rom/AScript_org_puremvc_lua_multicore_help_oop.lua /data/local/tmp/script
	adb push script/rom/rom.lua /data/local/tmp/script
	adb push script/rom/test.lua /data/local/tmp/script

clean:
	@rm -rf obj libs

elf:
	ndk-build.cmd -C jni/tracer
	adb push libs/x86/elf /data/local/tmp/elf
	adb shell chmod 777 /data/local/tmp/elf

mtail:
	ndk-build.cmd -C jni/tracer
	adb push libs/x86/mtail /data/local/tmp/mtail
	adb shell chmod 777 /data/local/tmp/mtail


ragnarokMono:
	$(MAKE) -C mono/rom

ragnarok:
	adb push  jni/luaServer/ragnarok.lua /data/local/tmp

libmog:
	adb shell cp /data/local/tmp/libloader.so /system/lib/libmog.so

liblog:
	adb shell cp /system/lib/liblog.so /system/lib/libmog.so

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

TOLUA=jni/tolua/bin/tolua.exe
jni/luaServer/lua_server.cpp:	jni/luaServer/lua_server.luapkg
	$(TOLUA) -n lua_server -o jni/luaServer/lua_server.cpp -H jni/luaServer/lua_server.hpp jni/luaServer/lua_server.luapkg
	