all: meteo

meteo: meteo.o procedure.o
	gcc -o meteo meteo.o procedure.o ../monitor_hoare/monitor.o

meteo.o: meteo.c header.h
	gcc -c -o meteo.o meteo.c

procedure.o: procedure.c header.h
	gcc -c -o procedure.o procedure.c

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf meteo
