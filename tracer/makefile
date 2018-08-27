CC=arm-linux-androideabi-gcc
CFLAGS=-I.


all:	tracer.bin

clean:
	rm tracer.bin

tracer.bin:	tracer.c
	$(CC) tracer.c -o tracer.bin -I.
	adb push tracer.bin data/local/tmp
	adb shell chmod 755 data/local/tmp/tracer.bin
	
install:
	adb push tracer.bin data/local/tmp
	adb shell chmod 755 data/local/tmp/tracer.bin
	

