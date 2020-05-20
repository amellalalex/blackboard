/*
* ipc.c
*
*   purpose: act a middleman between processes to complete communication requests
*   author: alex amellal
*
*/

// Project Headers
#include "client_t.h"
#include "client_handler.h"

// Standard C Libraries
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

// Placeholder for clients
static client_t clients[5];
static int      clients_len;

// Placeholder for client handlers
static pthread_t  client_handlers[5];
static int        client_handlers_len;

int main()
{
  // Create placeholder for socket
  int sock;

  // Create socket
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) // socket() failed
  {
    perror("socket() failed");
    return -1;
  }

  // Create placeholder for socket address
  const struct sockaddr_un address = {
    .sun_family = AF_UNIX,
    .sun_path   = "socket.socket"
  };
  socklen_t address_len = sizeof(address);

  // Unlink socket
  if(unlink(address.sun_path) == -1) // unlink() failed
  {
    perror("unlink() failed");
    return -1;
  }

  // Bind socket to address
  if(bind(sock, (struct sockaddr *) &address, address_len) == -1) // bind() failed
  {
    perror("bind() failed");
    return -1;
  }

  // Start listening for up to 5 incoming clients
  if(listen(sock, 5) == -1) // listen() failed
  {
    perror("listen() failed");
    return -1;
  }

  // Initialize client placeholders
  for(int x = 0; x < 5; x++) clients[x].conn = 0;
  clients_len = 0;

  // Initialize client handlers counter
  client_handlers_len = 0;

  // Initialize client placeholders for client handlers
  client_handler_clients = clients;
  client_handler_clients_len = &clients_len;

  // Accept incoming connections
  int conn;
  while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  {
    // Create placeholder for client name
    char name[3];

    // Receive client name
    if(read(conn, name, 3) <= 0) // read() failed
    {
      perror("read() failed");
      fprintf(stderr, "error reading client name. skipping to next in queue...\n");
      continue;
    }

    // Store client attributes in placeholder
    clients[clients_len].conn = conn;
    strcpy(clients[clients_len].name, name);

    // Update client count
    clients_len++;

    // Start handler thread
    if(pthread_create(&client_handlers[client_handlers_len], NULL, handle_client, (void *) &clients[client_handlers_len]) != 0) // pthread_create() failed
    {
      perror("pthread_create() failed");
      fprintf(stderr, "failed to start client handler #%d, skipping to next one...\n", client_handlers_len);
      continue;
    }

    // Update client handlers counter
    client_handlers_len++;
  }

  // IDEA: watchdog thread to wait for threads to terminate?

  // Wait for client handlers to terminate
  for(int x = 0; x < client_handlers_len; x++) pthread_join(client_handlers[x], NULL);

  // Close remaining client connections
  for(int x = 0; x < clients_len; x++) if(clients[x].conn != 0) close(clients[x].conn);

  // Close socket
  close(sock);

  // done
  return 0;
}

// // Returns pointer to client if client found with matching name.
// // Return NULL if no such client found.
// client_t * get_client(char * name)
// {
//   for(int x = 0; x < clients_len; x++) if(strcmp(clients[x].name, name) == 0) return &clients[x];
//   return NULL;
// }
