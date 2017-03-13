build: main.obj hashtable.obj
	cl /Fetema1.exe main.obj hashtable.obj hash.lib

main.obj: main.c
	cl /W3 /D_CRT_SECURE_NO_DEPRECATE /Fomain.obj /c main.c

hashtable.obj: hashtable.c
	cl /W3 /D_CRT_SECURE_NO_DEPRECATE /Fohashtable.obj /c hashtable.c

clean:
	del *.obj *.exe