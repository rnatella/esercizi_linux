#ifndef __HEADER__
#define __HEADER__

#include <sys/types.h>

#define TOTALE_SERVER 3
#define TOTALE_CLIENT 8
#define TOTALE_MESSAGGI 15


struct messaggio {
	long tipo;
	pid_t PID;
};


void Client(int msg_id_balancer);
void Balancer(int msg_id_balancer, int msg_id_server[]);
void Server(int msg_id_server);


#endif /* __HEADER__ */
