#ifndef EXEC_3_HPP_INCLUDED
#define EXEC_3_HPP_INCLUDED
#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

string exec_3(const string &cmd)
{
    ostringstream oss;
    fstream os;
    fstream err;
    string command = "./" + cmd;
  // run a process and create a streambuf that reads its stdout and stderr

  pipexec(command.c_str(), os);
  std::string line;
  // read child's stdout
  while (std::getline(os, line))
    oss  << line << '\n';
  // if reading stdout stopped at EOF then reset the state:
  if (os.eof() && os.fail())
    os.clear();
  // read child's stderr
  while (std::getline(err, line))
    oss << "stderr: " << line << '\n';


return oss.str();
}


#endif // EXEC_3_HPP_INCLUDED
