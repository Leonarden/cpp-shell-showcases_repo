#ifndef SYSTEM_2_HPP_INCLUDED
#define SYSTEM_2_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>

std::string ssystem (const char *command) {
    char tmpname [L_tmpnam];
    std::tmpnam ( tmpname );
    std::string scommand = command;
    std::string cmd = scommand + " >> " + tmpname;
    std::system(cmd.c_str());
    std::ifstream file(tmpname, std::ios::in | std::ios::binary );
    std::string result;
    if (file) {
        while (!file.eof()) result.push_back(file.get())
            ;
        file.close();
    }
    remove(tmpname);
    return result;
}



#endif // SYSTEM_2_HPP_INCLUDED
