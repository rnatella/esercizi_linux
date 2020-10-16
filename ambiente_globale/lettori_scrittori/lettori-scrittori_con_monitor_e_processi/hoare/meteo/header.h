//#include <stdbool.h>
#include "../monitor_hoare/monitor.h"

#define NUM_UTENTI 10
#define NUM_CONDITIONS 2

#define SYNCHL 0
#define SYNCHS 1

typedef struct {
	int temperatura;
	unsigned int umidita;
	unsigned short pioggia;
} meteo;

typedef struct {
	meteo meteo;
	unsigned short occupato;
	unsigned int numlettori;
} Buffer;



void Servizio(Monitor* m, Buffer * buf);
void Utente(Monitor* m, Buffer * buf);
