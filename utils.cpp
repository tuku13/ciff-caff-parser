//
// Created by Martin on 2023. 05. 18..
//

#include <iostream>
#include "utils.h"

Pixel utils::readAsPixel(std::ifstream &file) {
    char data[3];
    file.readsome(data, 3);
    return Pixel(data[0], data[1], data[2]);
}

int utils::covertToInt(const char *data) {
    int value = 0;
    for (int i = 0; i <= sizeof(&data) - 1; i++) {
        value += static_cast<unsigned char>(data[i]) * 1 << (8 * i);
    }
    return value;
}

int utils::covertToInt(const char *data, int bytes) {
    int value = 0;
    for (int i = 0; i < bytes; i++) {
        value = (value << 8) | static_cast<unsigned char>(data[i]);
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
