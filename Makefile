build: main.obj hashtable.obj
	cl /Fetema1.exe main.obj hashtable.obj hash.lib

main.obj: main.c
	cl /Fomain.obj /c main.c

hashtable.obj: hashtable.c
	cl /Fohashtable.obj /c hashtable.c

clean:
	del *.obj *.exe