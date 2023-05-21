//
// Created by Martin on 2023. 05. 18..
//

#include <iostream>
#include "utils.h"

int utils::covertToInt(const char *data) {
    int value = 0;
    for (int i = 0; i <= sizeof(&data) - 1; i++) {
        value += static_cast<unsigned char>(data[i]) * 1 << (8 * i);
    }
    return value;
}

int utils::readAsInt(std::ifstream &file, const int bytes) {
    char data[bytes];
    file.readsome(data, bytes);
    return covertToInt(data);
}

std::string utils::readAsString(std::ifstream &file, const int length) {
    char bytes[length + 1];
    file.read(bytes, length);
    bytes[length] = '\0';
    return bytes;
}
