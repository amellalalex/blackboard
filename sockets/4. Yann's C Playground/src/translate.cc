//author: yann guerin
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>
#include <cstring>

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

/*
  // Iterate through key-value pairs
  map<string, string>::iterator iter;
  for(iter = payload_commands.begin(); iter != payload_commands.end(); ++iter)
  {
    string key = iter->first;
    if (strcmp(command.c_str(), key.c_str())){
      code += iter->second;
    }
  }*/
  //map<string, string>::iterator iter;
  string word = "";
  for(int i = 0; i<command.length(); i++)
  {
    if (command.at(i) == ' ')
    {
      cout << word << endl;
      /*for(iter = payload_commands.begin(); iter != payload_commands.end(); ++iter)
      {
        string key = iter->first;
        if (strcmp(word.c_str(), key.c_str())){
          code += iter->second;
          cout << code << " " << word;
        }
      }*/
      map<string, string>::iterator pos = payload_commands.find(word);
      string value;
      if (pos == payload_commands.end()) {
        //handle the error
        continue;
      } else {
        value = pos->second;
      }
      cout << value << " is the value";
      value = "";
      word = "";
    }
    else
    {
      word = word + command.at(i);
    }
  }

  cout << "Payload Command: " << code;
  //11 13 10 00 12 03 01 02

  return 0;
}
