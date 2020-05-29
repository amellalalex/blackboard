//author: yann guerin
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>

using namespace std;

int main()
{
  map<string, string> payload_commands;

  payload_commands.insert(pair<string, string>("initialize",   "00"));
  payload_commands.insert(pair<string, string>("shutdown",     "01"));
  payload_commands.insert(pair<string, string>("take picture", "02"));
  payload_commands.insert(pair<string, string>("settings",     "03"));
  payload_commands.insert(pair<string, string>("format",       "10"));
  payload_commands.insert(pair<string, string>("filename",     "11"));
  payload_commands.insert(pair<string, string>("quality",      "12"));
  payload_commands.insert(pair<string, string>("filepath",     "13"));

  string command = "initialize payload to settings with format then take picture before shutdown";
  //0003100201

  string code;

  // Iterate through key-value pairs
  map<string, string>::iterator iter;
  for(iter = payload_commands.begin(); iter != payload_commands.end(); ++iter)
  {
    string key = iter->first;
    if (strcmp(command.c_str(), key.c_str())){
      code += iter->second;
    }
  }

  cout << "Payload Command: " << code;

  return 0;
}
