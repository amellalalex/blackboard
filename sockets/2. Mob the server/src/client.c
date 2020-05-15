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

  // Create placeholders for threads
  pthread_t listener, sender;

  // Start threads
  pthread_create(&listener, NULL, client_start_listening, (void *) &sock));
  pthread_create(&sender,   NULL, client_start_sending,   (void *) &sock));

  // Wait for threads to terminate
  pthread_join(listener,  NULL);
  pthread_join(sender,    NULL);

  // Close socket
  close(sock);

  // done
  return 0;
}

void * client_start_listening(void * parameters)
{
  // Creat placeholder for socket
  int socket = *((int *) parameters);

  // Create placeholder for bytes read
  int bytes_read = -1;

  // Create placeholder for incoming message
  char msg[128];

  // Listen for incoming data
  while((bytes_read = read(sock, (void *) msg, 128)) != -1)
  {

  }

  // Check read status
  if(bytes_read == -1)
  {
    perror("read() failed");
  }

  pthread_exit(NULL);
}

void * client_start_sending(void * parameters)
{
  pthread_exit(NULL);
}
