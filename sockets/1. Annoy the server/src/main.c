#include "server.h"
#include "client.h"

#include <string.h>

int main(int argc, char * argv[])
{
  // Check argument count
  if(argc < 2)
  {
    fprintf(stderr, "Invalid number of arguments\n");
    fprintf(stderr, "Try: ./sockets <server/client>\n");
    return -1;
  }

  // start server
  if(strcmp(argv[1], "server") == 0)
  {
    if(server_start() == -1) // server_start() failed
    {
      fprintf(stderr, "server_start() failed\n");
      return -1;
    }
  }

  // start client
  else if(strcmp(argv[1], "client") == 0)
  {
    if(client_start() == -1) // client_start() failed
    {
      fprintf(stderr, "client_start() failed\n");
      return -1;
    }
  }

  // invalid argument
  else
    fprintf(stderr, "Invalid argument: %s\n", argv[1]);

  return 0;
}
