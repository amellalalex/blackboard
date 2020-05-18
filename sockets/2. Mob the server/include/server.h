#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <pthread.h>

// Methods
int server_start();

// Threads
void * server_start_listening (void * parameters);
void * server_start_sending   (void * parameters);

#endif /* end of include guard: SERVER_H */
