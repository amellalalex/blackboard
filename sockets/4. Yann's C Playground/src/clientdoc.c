#include "client.h"

static int sock;

int start_theClient()
{
  //if statements check for error and then perror catch error then print the string to terminal followed by the error
  //create socket: parameters include comm. protocol, type(TCP v. UDP), protocol for socket(0 cause this sock only has one option)
  if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
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

  //Connect to the socket with parameters : the socket, pointer to the address struct, and a pointer to the size of address
  if(connect(sock, (struct sockaddr *) &address, sizeof(address)) == -1)
  {
    perror("Error with connect(): ");
    return -1;
  }

  //placeholder for message variable
  char msg[128];

  //get the user input for the message
  printf("Enter the message to be send: ");
  fgets(msg, 128, stdin);

  //Send message through the socket by write with parameters : socket to send through, constant void pointer of message(since its local to computer), and length of message in bytes to be sent
  if((write(sock, (const void *) msg, strlen(msg))) == -1)
  {
    perror("Error with write(): ");
    return -1;
  }

  //Once message is sent, close the socket
  close(sock);

  return 0;
}
