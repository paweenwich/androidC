for %%s in (62001,62025,62026,62027) do (
	adb kill-server
	ping 127.0.0.1 -n 3 > nul
	adb connect 127.0.0.1:%%s
	c:\cygwin64\bin\bash -c "/usr/bin/make rom"
)

