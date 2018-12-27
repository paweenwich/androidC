#!/system/bin/sh
if [ $# -ne 2 ] ; then
    echo './install.sh I|U|S filename'
    exit 1
fi

if [ "$1" = "I" ] ; then
    echo "Install"
    ./elf ADDSO $2 $2.out libmog.so
    cp $2.out /data/app-lib/com.gravity.romg-2/$2
fi

if [ "$1" = "U" ] ; then
    echo "UnInstall"
    cp $2 /data/app-lib/com.gravity.romg-2/$2
fi

if [ "$1" = "S" ] ; then
    mount -o remount,rw /system
    cp $2 /system/lib/libmog.so
fi

