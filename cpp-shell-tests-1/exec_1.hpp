#ifndef EXEC_1_HPP_INCLUDED
#define EXEC_1_HPP_INCLUDED
#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

std::string exec_1(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}




#endif // EXEC_1_HPP_INCLUDED
