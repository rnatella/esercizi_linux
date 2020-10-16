start: main.o procedure.o monitor.o
	gcc -o start main.o procedure.o monitor.o

main.o: main.c header.h
	gcc -o main.o -c main.c

procedure.o: procedure.c header.h
	gcc -o procedure.o -c procedure.c

monitor.o: monitor.c monitor.h
	gcc -o monitor.o -c monitor.c

clean:
	rm -f *.o
	rm -f start
