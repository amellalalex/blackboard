/*
* serialize.h
*
*   purpose:  serialize a map into a string for simple sending through the IPC
*   author:   Yann Guerin
*
*/

#ifndef SOCKETS_CROWDCONTROL_INCLUDE_SERIALIZE_H
#define SOCKETS_CROWDCONTROL_INCLUDE_SERIALIZE_H

// Standard C Libraries
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>

//The serializing functions
string serialize_StoS(map<string,string> map);
string serialize_StoI(std::map<string, int> map);
string serialize_ItoS(std::map<int, string> map);
string serialize_ItoI(std::map<int, int> map);

#endif /* end of include guard: SOCKETS_CROWDCONTROL_INCLUDE_SERIALIZE_H */
