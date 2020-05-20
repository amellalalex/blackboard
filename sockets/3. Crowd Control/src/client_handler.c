/*
* client_handler.c
*
*   purpose:  handle client connections to the IPC. intended to be used as a thread.
*   author:   alex amellal
*
*   request formatting: <destination client name> <message>
*/

#include "client_handler.h"

// Clients array placeholder
static client_t  * clients      = NULL;
static int       * clients_len  = NULL;

void * handle_client(void * p)
{
  // Check if clients array placeholders are initialized
  if(clients == NULL || clients_len == NULL)
  {
    fprintf(stderr, "clients array placeholder for client handler not initialized. refusing to proceed.\n");
    pthread_exit(NULL);
  }

  // Create placeholder for clients pointer
  client_t * client = (client_t *) p;

  // Create placeholders for client request
  char  req[MAX_MSG_LEN];
  int   req_len;
  char  dest_name[3];
  char  message[MAX_MSG_LEN];

  // Handle incoming requests from client
  while((req_len = read(client->conn, req, MAX_MSG_LEN)) > 0)
  {
    // Check if request is at least <3 char> + space + <1 char> = 5 in length
    if(req_len < 4) // request is too short
    {
      fprintf(stderr, "client %s made a request that was too short. ignoring.\n", client->name);
      continue;
    }

    // Add null termination character to request
    req[req_len] = '\0';

    // Check if client requesting to exit
    if(strcmp(req, "exit") == 0) break;

    // Extract destination client name from request
    strncpy(dest_name, req, 3);

    // Create placeholder for destination client index in clients array
    int dest_client_index = -1;

    // Identify destination client within clients array
    for(int x = 0; x < *clients_len; x++)
    {
      // Check if name matches
      if(strncmp((clients + x)->name, dest_name, 3) == 0) // name matches
      {
        dest_client_index = x;
        break;
      }
    }

    // Check if client found
    if(dest_client_index == -1) // client not found
    {
      // Skip request
      continue;
    }

    // Front message with request sender
    sprintf(message, "%s ", client->name);

    // Extract message from request
    for(int x = 4; x < strlen(req); x++) message[x] = req[x];

    // Add null termination character to message
    message[strlen(req)] = '\0';

    // Send message to destination client
    if(write((clients + dest_client_index)->conn, message, strlen(message)) < strlen(message)) // write() failed
    {
      perror("write() failed");
      fprintf(stderr, "wrote %d/%d bytes from clients %.3s to %.3s. skipping to next client request.\n");
      continue;
    }
  }

  // Close connection to client
  close(client->conn);

  // done
  pthread_exit(NULL);
}

// Sets clients array pointer
void set_clients(client_t * clients_)
{
  // Set local clients to clients parameter
  clients = clients_;
}

// Sets clients_len pointer
void set_clients_len(int * clients_len_)
{
  // Set local clients_len to clients_len parameter
  clients_len = clients_len_;
}
