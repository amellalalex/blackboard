#include "server.h"

static int sock;

int start_theServer()
{
  //if statements check for error and then perror catch error then print the string to terminal followed by the error
  //create socket: parameters include comm. protocol, type(TCP v. UDP), protocol for socket(0 cause this sock only has one option)
  if((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
  {
    perror("Error with Socket(): ");
    return -1;
  }

  //create a struct for the address of the socket (sockaddr_un is the type, address is the name)
  const struct sockaddr_un address =
  {
    //sun family is the comm. protocol for the address/socket
    .sun_family = AF_UNIX,
    //sun path is the directory where the client and server will communicate from
    .sun_path   = "./tunnel.socket",
  };

  //unlink socket from the address so that it may be reused by a new socket
  if(unlink(address.sun_path) == -1)
  {
    perror("Error with Unlink(): ");
    return -1;
  }

  //bind to socket with parameters : the socket variable, a pointer to the address struct, and the size of the address
  if((bind(sock, (struct sockaddr *) &address, sizeof(address))) == -1)
  {
    perror("Error with Bind(): ");
    return -1;
  }

  //listen parameters : the socket, and maximum number of connection to listen for
  if((listen(sock, 5)) == -1)
  {
    perror("Error with Listen(): ");
    return -1;
  }

  //variable for the size of address to be pointed to in accept()
  socklen_t address_len = sizeof(address);
  //placeholder for connection variable
  int conn;

  //while there are still connection to be accepted, accept and store in variable conn
  //socket connection with parameters : the socket, pointer to the address struct, and a pointer to the size of address
  while((conn = accept(sock, (struct sockaddr *) &address, &address_len)) != -1)
  {
    //placeholder for the incoming message
    char msg[128];
    //variable for bytes read to check for error when no bytes are read
    int bytes_read = -1;

    //read the incoming message with parameters : connection variable, void pointer to message, to a maximum of 128 bytes
    //and store in variable bytes_read the number of bytes in the message
    while((bytes_read = read(conn, (void *) msg, 128)) == -1)
    {
      perror("Error with read(): ");
      //while nothing is being read keep sleeping until there is an incoming messgae
      sleep(1);
    }

    //add a termination character to the end of the message to inform C that the message is complete
    msg[bytes_read] = "\0";

    //Print the message
    printf("Incoming message: %s\n", msg);

    //Close the connection to free the socket for a new connection
    close(conn);
  }

  //Check to see if connection establishment failed
  if(conn == -1)
  {
    perror("Error with connection: ");
    return -1;
  }

  //Once all is done, close the socket
  close(sock);

  return 0;
}
