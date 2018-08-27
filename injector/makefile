CC=arm-linux-androideabi-g++
CFLAGS=-I.
DEPS = trace.hpp

-include $(DEP)

all:	injector.bin

clean:
	rm injector.bin

injector.bin: main.cpp
	$(CC) main.cpp -o injector.bin -I.
	adb push injector.bin data/local/tmp
	adb shell chmod 755 data/local/tmp/injector.bin
	
	
install:
	adb push injector.bin data/local/tmp
	adb shell chmod 755 data/local/tmp/injector.bin
	

