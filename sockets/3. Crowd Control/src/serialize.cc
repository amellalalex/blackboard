/*
* serialize.cc
*
*   purpose:  serialize a map into a string for simple sending through the IPC
*   author:   Yann Guerin
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

string serialize_StoS(map<string,string> map);
string serialize_StoI(std::map<string, int> map);
string serialize_ItoS(std::map<int, string> map);
string serialize_ItoI(std::map<int, int> map);


int main()
{
  // Create map placeholder
  map<string, int> coordinates;

/*
  // Insert key-value pairs
  coordinates.insert(pair<string, string>("initialize",   "00"));
  coordinates.insert(pair<string, string>("shutdown",     "01"));
  coordinates.insert(pair<string, string>("take picture", "02"));
  coordinates.insert(pair<string, string>("settings",     "03"));
  coordinates.insert(pair<string, string>("format",       "10"));
  coordinates.insert(pair<string, string>("filename",     "11"));
  coordinates.insert(pair<string, string>("quality",      "12"));
  coordinates.insert(pair<string, string>("filepath",     "13"));
*/
  // Insert key-value pairs
  coordinates.insert(pair<string, int>("initialize",   00));
  coordinates.insert(pair<string, int>("shutdown",     01));
  coordinates.insert(pair<string, int>("take picture", 02));
  coordinates.insert(pair<string, int>("settings",     03));
  coordinates.insert(pair<string, int>("format",       10));
  coordinates.insert(pair<string, int>("filename",     11));
  coordinates.insert(pair<string, int>("quality",      12));
  coordinates.insert(pair<string, int>("filepath",     13));


  string command = serialize_StoI(coordinates);
  cout << "The map in string form is: \n" << command;

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
    map_data_len += iter->second.length();  // value
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
string serialize_StoS(std::map<string, string> map)
{
  // Create iterator
  std::map<string, string>::iterator iter;
  string message = "";
  // Iterate through key-value pairs
  for(iter = map.begin(); iter != map.end(); ++iter)
  {
    message = message + iter->first + "::" + iter->second + "::";
  }
  return message;
}

string serialize_StoI(std::map<string, int> map)
{
  // Create iterator
  std::map<string, int>::iterator iter;
  std::string message = "";
  // Iterate through key-value pairs
  for(iter = map.begin(); iter != map.end(); ++iter)
  {
    std::string cast = std::to_string(iter->second);
    message = message + iter->first + "::" + cast + "::";
  }
  return message;
}


string serialize_ItoS(std::map<int, string> map)
{
  // Create iterator
  std::map<int, string>::iterator iter;
  string message = "";
  // Iterate through key-value pairs
  for(iter = map.begin(); iter != map.end(); ++iter)
  {
    string cast = std::to_string(iter->first);
    message = message + cast + "::" + iter->second + "::";
  }
  return message;
}

string serialize_ItoI(std::map<int, int> map)
{
  // Create iterator
  std::map<int, int>::iterator iter;
  string message = "";
  // Iterate through key-value pairs
  for(iter = map.begin(); iter != map.end(); ++iter)
  {
    string cast = std::to_string(iter->first);
    string cast2 = std::to_string(iter->second);
    message = message + cast + "::" + cast2 + "::";
  }
  return message;
}
