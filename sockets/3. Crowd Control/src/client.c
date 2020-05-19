/*
* client.c
*
*   purpose: connects to the ipc with a specific name and the ability to send messages to other clients
*   author: alex amellal
*
*/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
  // Check argc
  if(argc != 2)
  {
    fprintf(stderr, "Invalid number of arguments\n Try: ./client <name>\n");
    return -1;
  }

  // Create placeholder for client name
  char * name = argv[1];

  // Create placeholder for socket address
  const struct sockaddr_un address = {
    .sun_family = AF_UNIX,
    .sun_path   = "./socket.socket"
  };
  socklen_t address_len = sizeof(address);

  // Create socket placeholder
  int sock;

  // Initiate socket
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) // socket() failed
  {
    perror("socket() failed");
    return -1;
  }

  // Connect to host
  if(connect(sock, (struct sockaddr *) &address, address_len) == -1) // connect() failed
  {
    perror("connect() failed");
    return -1;
  }

  // Send name to host
  if(write(sock, name, strlen(name)) < strlen(name)) // write() failed
  {
    perror("write() failed");
    return -1;
  }

  // Create placeholder for incoming messages
  char msg[128];
  int msg_len = -1;

  // Await for incoming messages
  while((msg_len = read(sock, msg, 128)) > 0) // until a 0 length message is read or error is encountered
  {
    // Null-terminate message
    msg[msg_len] = '\0';

    // Check if message is 'exit'
    if(strcmp(msg, "exit") == 0) break;

    // Prompt user with incoming message
    printf("Incoming message: %s\n", msg);
  }

  // Close socket connection
  close(sock);

  // done
  return 0;
}
