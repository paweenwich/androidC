##!/system/bin/sh
if [ $# -ne 2 ] ; then
    echo './install.sh I|U|S|D filename'
    exit 1
fi

#find correct directory
DIRECTORY=/data/app-lib/com.gravity.romg-2
INSTALLDIR=/data/local/tmp
if [ ! -d "$DIRECTORY" ]; then
    # Control will enter here if $DIRECTORY exists.
    DIRECTORY=/data/app-lib/com.gravity.romg-1
    if [ ! -d "$DIRECTORY" ]; then
	echo "/data/app-lib/com.gravity.romg-[1|2] not found"
	exit 1
    fi
fi

if [ "$1" = "S" ] ; then
    mount -o remount,rw /system
    cp $2 /system/lib/libmog.so
fi

if [ "$1" = "I" ] ; then
    echo "Install at $DIRECTORY"
    ./elf ADDSO $2 $2.out libmog.so
    cp $2.out $DIRECTORY/$2
fi

if [ "$1" = "U" ] ; then
    echo "UnInstall at $DIRECTORY"
    cp $2 $DIRECTORY/$2
fi

if [ "$1" = "D" ] ; then
    #check directory exist
    if [ ! -d "$INSTALLDIR/script" ]; then
	mkdir $INSTALLDIR/script
	chmod 777 $INSTALLDIR/script
    fi
    if [ ! -d "$INSTALLDIR/loadbufferx" ]; then
	mkdir $INSTALLDIR/loadbufferx
	chmod 777 $INSTALLDIR/loadbufferx
    fi
    chmod 777 /data/local/tmp
fi

