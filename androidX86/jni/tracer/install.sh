##!/system/bin/sh
if [ $# -ne 2 ] ; then
    echo './install.sh I|U|S filename'
    exit 1
fi

#find correct directory
DIRECTORY=/data/app-lib/com.gravity.romg-2
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


