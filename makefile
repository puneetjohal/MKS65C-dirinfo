all: dirinfo.o
	gcc dirinfo.o

run: all
	./a.out

file.o: dirinfo.c
	gcc -c dirinfo.c

clear:
	rm *
