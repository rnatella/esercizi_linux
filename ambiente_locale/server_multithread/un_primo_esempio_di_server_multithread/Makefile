all: Start

Start: Main.o Procedure.o
	gcc -g -o Start Main.o Procedure.o -pthread

main.o: Main.c Header.h
	gcc -g -c Main.c

Procedure.o: Procedure.c Header.h
	gcc -g -c Procedure.c

clean:
	rm -f *.o
	rm -f ./Start
