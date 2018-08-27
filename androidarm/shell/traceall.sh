for filename in /proc/$1/task/*
do
	fname=$(basename "$filename")
	echo $fname
	strace -i -p $fname -o "strace_$fname.txt" &
done
