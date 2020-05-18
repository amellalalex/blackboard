#include "server.h"

static int sock;

int server_start()
{
  // Create socket
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) // socket() failed
  {
    perror("socket() failed");
    return -1;
  }

  // Create placeholder for unix domain address
  const struct sockaddr_un address = {
    .sun_family = AF_UNIX,
    .sun_path   = "./tunnel.socket"
  };
  socklen_t address_len = sizeof(address);

  // Unlink socket
  if(unlink(address.sun_path) == -1) // unlink() failed
  {
    perror("unlink() failed");
    return -1;
  }

  // Bind socket
  if(bind(sock, (struct sockaddr *) &address, sizeof(address)) == -1) // bind() failed
  {
    perror("bind() failed");
    return -1;
  }

  // Start listening for up to 5 incoming connections
  if(listen(sock, 5) == -1) // listen() failed
  {
    perror("listen() failed");
    return -1;
  }

  // Create placeholder for incoming connection
  int conn;

  // Accept incoming connections until none left
  while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  {
    pthread_t server_listen, server_send;
    pthread_create(&server_listen, NULL, server_start_listening, (void *) &conn);
    pthread_create(&server_send, NULL, server_start_sending, (void *) &conn);
    if(server_start_listening((void *) &conn) == -1)
    {
      perror("Server start listening failed");
      return -1;
    }


/*
    // Create placeholder for incoming message
    char msg[128];

    // Create placeholder for bytes read
    int bytes_read = -1;

    // Receive message from client
    while((bytes_read = read(conn, (void *) msg, 128)) == -1) // read() failing
    {
      perror("read() failed");
      sleep(1);
    }

    // if(read(conn, (void *) msg, 128) == -1) // read() failed
    // {
    //   perror("read() failed");
    //   return -1;
    // }

    // Null terminate message
    msg[bytes_read] = '\0';

    // Print message
    printf("Incoming message from client: %s\n", msg);
*/
    // Close connection to client
    close(conn);
  }

  // Check connection status
  if(conn == -1) // connection error
  {
    perror("connection error");
    return -1;
  }

  // Close socket
  close(sock);

  // done
  return 0;
}

//Server start listening function to be threaded
void * server_start_listening(void * parameters)
{
  //Turn conn pointer back to int
  int conn = *((int *) parameters);

  // Create placeholder for incoming message
  char msg[128];

  // Create placeholder for bytes read
  int bytes_read = -1;

  // Receive message from client
  while((bytes_read = read(conn, (void *) msg, 128)) == -1) // read() failing
  {
    perror("read() failed");
    sleep(1);
  }

  // if(read(conn, (void *) msg, 128) == -1) // read() failed
  // {
  //   perror("read() failed");
  //   return -1;
  // }

  // Null terminate message
  msg[bytes_read] = '\0';

  // Print message
  printf("Incoming message from client: %s\n", msg);
}

void * server_start_sending(void * parameters)
{
  pthread_exit(NULL);
}
