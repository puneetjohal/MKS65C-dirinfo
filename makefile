all: dirinfo.o
	gcc dirinfo.o

run: all
	./a.out $(args)

file.o: dirinfo.c
	gcc -c dirinfo.c

clean:
	rm *.o
	rm *.out
