/*
* themaps.cc
*
*   Purpose: Deal with Comms to Command translation
*   Author: Yann Guerin, Alex Amellal
*
*/


#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>

using namespace std;

//int serialize_map(map<string, int> map, char ** serial_out);
//int serialize_map(map<string, int> map);

int main()
{
  //"payload-(settings):(format):(filename):(quality):(filepath);(take picture)"
  // Create map placeholder
  map<string, int> coordinates;

  // Insert key-value pairs
  coordinates.insert(pair<string, int>("initialize",   00));
  coordinates.insert(pair<string, int>("shutdown",     01));
  coordinates.insert(pair<string, int>("take picture", 02));
  coordinates.insert(pair<string, int>("settings",     03));
  coordinates.insert(pair<string, int>("format",       10));
  coordinates.insert(pair<string, int>("filename",     11));
  coordinates.insert(pair<string, int>("quality",      12));
  coordinates.insert(pair<string, int>("filepath",     13));

  // Iterate through key-value pairs
  map<string, int>::iterator iter;
  for(iter = coordinates.begin(); iter != coordinates.end(); ++iter)
  {
    cout << "Command options:\n";
    cout << iter->first << " , " << iter->second << endl;
  }

  string command = "initialize payload to settings with format then take picture before shutdown";
  //0003100201
  //char command[20];

  for(iter = coordinates.begin(); iter != coordinates.end(); ++iter)
  {
    string key = iter->first;
    if (strcmp(command, key)){
      command += iter->second;
    }
  }

  cout << command;
  // Print size of coordinates
  cout << "sizeof(coordinates) = " << sizeof(map<string, int>) << endl;

  //char * serial_map;
  //serialize_map(coordinates, &serial_map);

  // done
  return 0;
}
/*
int serialize_map(std::map<string, int> map, char ** serial_out)
{
  // Create iterator
  std::map<string, int>::iterator iter;

  // Measure memory allocation needed to serialize map
  size_t map_data_len = 0;
  for(iter = map.begin(); iter != map.end(); ++iter)
  {
    map_data_len += iter->first.length();   // key
    map_data_len += 2;//iter->second.length();  // value
    map_data_len++;                         // separator
  }

  // Allocate memory for serialized map
  char * result;
  if((result = (char *) malloc(map_data_len)) == NULL) // malloc() failed
  {
    cout << "Failed to allocate memory" << endl;
  }

  // Export pointer to serialized map
  *serial_out = result;

  // done
  return 0;
}
*/
