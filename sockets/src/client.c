#include "client.h"

int client_start()
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
    .sun_path   = "./tunnel.socket"
  };

  // Connect to server 
  if(connect(sock, (struct sockaddr *) &address, sizeof(address)) == -1) // connect() failed
  {
    perror("connect() failed");
    return -1;
  }

  // Create placeholder for next message
  char msg[128];

  // Get input from user
  printf("Enter a message to send to host: ");
  fgets(msg, 128, stdin);

  // Send message to server
  if(write(sock, (const void *) msg, strlen(msg)) == -1) // send() failed
  {
    perror("send() failed");
    return -1;
  }

  // Close socket
  close(sock);

  // done
  return 0;
}
