

MCS=/cygdrive/c/PROGRA~2/Mono-2.0.1/bin/mcs

all:	hello.dll

hello.dll:  hello.cs
	$(MCS) -r:./Managed/zlib.net.dll -target:library hello.cs