#pragma once
//
// Created by Martin on 2023. 05. 13..
//
#include <fstream>

namespace utils {
    int covertToInt(const char* data);
    int covertToInt(const char* data, int bytes);


    int readAsInt(std::ifstream &file, int bytes);

    std::string readAsString(std::ifstream &file, int length);
}
