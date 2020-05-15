#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <pthread.h>

int client_start();
void * client_start_listening(void * parameters);
void * client_start_sending(void * parameters);

#endif /* end of include guard: CLIENT_H */
