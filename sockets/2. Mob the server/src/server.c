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
  //int conn;

  // Accept incoming connections until none left
  //while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  //{
  pthread_t server_listen;
  pthread_create(&server_listen, NULL, server_start_listening, (void *) &sock, (void *) &address );
  //pthread_create(&server_send, NULL, server_start_sending, (void *) &conn);

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

  pthread_join(server_listen, NULL);
  //pthread_join(server_send,   NULL);
/*
  // Close connection to client
  close(conn);


  // Check connection status
  if(conn == -1) // connection error
  {
    perror("connection error");
    return -1;
  }
*/
  // Close socket
  close(sock);

  // done
  return 0;
}

//Server start listening function to be threaded
void * server_start_listening(void * parameter1, void * parameter2)
{
  //Turn sock pointer back to int
  int sock = *((int *) parameter1);
  struct address = *((struct *) parameter2);

  int conn;
  while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  {
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

  pthread_t server_send;
  pthread_create(&server_send, NULL, server_start_sending, (void *) &conn);

  pthread_join(server_send,   NULL);
  // Close connection to client
  close(conn);


  // Check connection status
  if(conn == -1) // connection error
  {
    perror("connection error");
    return -1;
  }
  // done
  pthread_exit(NULL);
}

void * server_start_sending(void * parameters)
{
  //Turn conn pointer back to int
  int conn = *((int *) parameters);

  //create placeholder for input
  char text[128];
  char *message = text;
  printf("What is the message for LORIS? \n");
  fgets(message, 128, stdin);

  //send message through connection
  if (write(conn, message, 128) == -1) {
    perror("Write to socket failed");
    pthread_exit(NULL);
  }
  //done
  pthread_exit(NULL);
}
