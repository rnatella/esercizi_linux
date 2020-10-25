all: prodcons

prodcons: main.o monitor.o prodcons.o
	gcc -o prodcons   main.o monitor.o prodcons.o

main.o: main.c prodcons.h
	gcc -c -o main.o  main.c

monitor.o: monitor.c monitor.h
	gcc -c -o monitor.o  monitor.c

prodcons.o: prodcons.c prodcons.h
	gcc -c -o prodcons.o  prodcons.c

clean:
	rm -f *.o
	rm -f prodcons