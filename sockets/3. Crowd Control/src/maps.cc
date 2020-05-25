#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>

using namespace std;

int serialize_map(map<string, string> map, char ** serial_out);
int serialize_map(map<int, int> map);

int main()
{
  // Create map placeholder
  map<string, string> coordinates;

  // Insert key-value pairs
  coordinates.insert(pair<string, string>("45.643490238N", "23.3490238E"));
  coordinates.insert(pair<string, string>("22.983823298N", "11.2930982E"));
  coordinates.insert(pair<string, string>("88.643490238N", "54.3490238E"));

  // Iterate through key-value pairs
  map<string, string>::iterator iter;
  for(iter = coordinates.begin(); iter != coordinates.end(); ++iter)
  {
    cout << iter->first << " , " << iter->second << endl;
  }

  // Print size of coordinates
  cout << "sizeof(coordinates) = " << sizeof(map<int, int>) << endl;

  char * serial_map;
  serialize_map(coordinates, &serial_map);

  // done
  return 0;
}

int serialize_map(std::map<string, string> map, char ** serial_out)
{
  // Create iterator
  std::map<string, string>::iterator iter;

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
