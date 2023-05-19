#pragma once
//
// Created by Martin on 2023. 05. 13..
//
#include <fstream>
#include "Pixel.h"

namespace utils {
    int covertToInt(const char* data);
    int covertToInt(const char* data, int bytes);


    int readAsInt(std::ifstream &file, int bytes);
    Pixel readAsPixel(std::ifstream &file);

    std::string readAsString(std::ifstream &file, int length);
}
