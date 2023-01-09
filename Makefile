libfakeudev.so: fakeudev.c
	gcc -shared -fPIC fakeudev.c -o libfakeudev.so -Wall -O2 -g
