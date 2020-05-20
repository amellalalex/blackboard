/*
* client_handler.h
*
*   purpose:  handle client connections to the IPC. intended to be used as a thread.
*   author:   alex amellal
*
*/

#ifndef SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_HANDLER_H
#define SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_HANDLER_H

// Project Headers
#include "settings.h"
#include "client_t.h"

// Standard C Libraries
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

// Set methods
void set_clients(client_t * clients);
void set_clients_len(int * clients_len);

// Thread methods
void * handle_client(void *);

#endif /* end of include guard: SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_HANDLER_H */
