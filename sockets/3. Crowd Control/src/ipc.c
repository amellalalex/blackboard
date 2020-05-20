/*
* ipc.c
*
*   purpose: act a middleman between processes to complete communication requests
*   author: alex amellal
*
*/

// Project Headers
#include "settings.h"
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
static client_t clients[MAX_NUM_CLI];
static int      clients_len;

// Placeholder for client handlers
static pthread_t  client_handlers[MAX_NUM_CLI];
static int        client_handlers_len;

// Threads
static void * watchdog();

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

  // Start listening for up to MAX_NUM_CLI incoming clients
  if(listen(sock, MAX_NUM_CLI) == -1) // listen() failed
  {
    perror("listen() failed");
    return -1;
  }

  // Initialize client placeholders
  for(int x = 0; x < MAX_NUM_CLI; x++) clients[x].conn = 0;
  clients_len = 0;

  // Initialize client handlers counter
  client_handlers_len = 0;

  // Initialize client placeholders for client handlers
  set_clients(clients);
  set_clients_len(&clients_len);

  // Accept incoming connections
  int conn;
  while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  {
    // Check if number of clients is within limit
    if(clients_len >= MAX_NUM_CLI) // wait until an opening appears
    {
      for(;;)
      {
        // Sleep for a second
        sleep(1);

        // Check value
        if(clients_len < MAX_NUM_CLI) break;
      }
    }

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
    if(pthread_create(&client_handlers[next_cli], NULL, handle_client_requests, (void *) &clients[next_cli]) != 0) // pthread_create() failed
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
