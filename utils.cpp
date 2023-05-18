//
// Created by Martin on 2023. 05. 18..
//

#include "utils.h"

int utils::covertToInt(const char *data) {
    int value = static_cast<int>(static_cast<unsigned char>(*data));
    return value;
}

int utils::readAsInt(std::ifstream &file, const int bytes) {
    char data[bytes];
    file.read(data, bytes);
    return covertToInt(data);
}

std::string utils::readAsString(std::ifstream &file, const int length) {
    char bytes[length + 1];
    file.read(bytes, length);
    bytes[length] = '\0';
    return bytes;
}
