/*
* client_t.h
*
*   purpose:  defines client connection placeholder structure for IPC.
*   author:   alex amellal
*
*/

#ifndef SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_T_H
#define SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_T_H

typedef struct Client
{
  int   conn;     // connection socket placeholder
  char  name[3];  // client name placeholder
} client_t;

#endif /* end of include guard: SOCKETS_CROWDCONTROL_INCLUDE_CLIENT_T_H */
