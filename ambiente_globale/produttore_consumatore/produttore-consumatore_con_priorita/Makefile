

all: main.o procedure.o monitor_sc.o
	gcc -o start main.o procedure.o monitor_sc.o

main.o: main.c procedure.o monitor_sc.o
	gcc -c main.c

procedure.o: procedure.c procedure.h monitor_sc.o
	gcc -c procedure.c

monitor_sc.o: monitor_sc.c monitor.h
	gcc -c monitor_sc.c
      
clean:
	rm -f *.o 
	rm -f *~
	rm -f start

