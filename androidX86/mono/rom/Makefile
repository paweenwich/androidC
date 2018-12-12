

MCS=/cygdrive/c/PROGRA~2/Mono-2.0.1/bin/mcs

all:	hello.dll hello.exe

hello.dll:  hello.cs
	$(MCS) -r:zlib.net.dll -target:library hello.cs 
	adb push hello.dll /data/local/tmp/hello.dll

./Managed/hello.exe:  hello.cs
	$(MCS) -r:zlib.net.dll hello.cs -o:hello.exe