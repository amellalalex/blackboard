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

// Placeholder for client handlers
static pthread_t client_handlers[MAX_NUM_CLI];

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

  //Create socket pointer placeholder
  FILE *socket_file;
  //Check if the socket.socket file exists
  if (access("./socket.socket", F_OK) == -1) { //yes so close the file
    socket_file = fopen("./socket.socket", "w+");
    printf("The file, socket.socket, has been created\n");
    fclose(socket_file);
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
  for(int x = 0; x < MAX_NUM_CLI; x++) clients[x].conn = -1;

  // Initialize client placeholders for client handlers
  set_clients(clients);

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
    /*
    //Check if the client name is already in use
    // Parse through clients
    for(int x = 0; x < MAX_NUM_CLI; x++)
    {
      //check if the new client name is already in use
      if(strcmp(name, clients[x]) == 0)
      {
        //if yes, remove the previous user (or stop the new user **discuss with alex based on bug)
        clients[x] = -1;
      }
    }
    */
    // Find next available client placeholder
    int next_cli;
    if((next_cli = get_free_client()) == -1) // no free client found
    {
      // Wait until client placeholder is free
      for(;;)
      {
        // Wait a second
        sleep(1);

        // Check for free client
        if((next_cli = get_free_client()) != -1) break;
      }
    }

    // Store client attributes in placeholder
    clients[next_cli].conn = conn;
    strcpy(clients[next_cli].name, name);

    // Start handler thread
    if(pthread_create(&client_handlers[next_cli], NULL, handle_client_requests, (void *) &clients[next_cli]) != 0) // pthread_create() failed
    {
      perror("pthread_create() failed");
      fprintf(stderr, "failed to start client handler #%d, skipping to next one...\n", next_cli);
      continue;
    }
  }

  // Close remaining client connections
  for(int x = 0; x < MAX_NUM_CLI; x++) if(clients[x].conn != -1) close(clients[x].conn);

  // Close socket
  close(sock);

  // done
  return 0;
}
