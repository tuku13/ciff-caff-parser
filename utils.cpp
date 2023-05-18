//
// Created by Martin on 2023. 05. 18..
//

#include <iostream>
#include "utils.h"

int utils::covertToInt(const char *data) {
    for (int i = 0; i <= sizeof(data) - 1; i++) {
        std::cout << std::to_string(data[i]) << " ";
    }
    std::cout << std::endl;
//    std::cout << "-> ";

    char dataInverse[sizeof(data)];
    for (int i = 0; i <= sizeof(data) - 1; i++) {
        dataInverse[i] = data[sizeof(data) - 1 - i];
    }
    for (int i = 0; i <= sizeof(data) - 1; i++) {
        std::cout << std::to_string(dataInverse[i]) << " ";
    }
    std::cout << std::endl;

    int value = covertToInt(data, 1);
    std::cout << value << " | " << covertToInt(dataInverse, sizeof(data)) << std::endl;
    std::cout << std::endl;
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
    file.read(data, bytes);
    return covertToInt(data);
}

std::string utils::readAsString(std::ifstream &file, const int length) {
    char bytes[length + 1];
    file.read(bytes, length);
    bytes[length] = '\0';
    return bytes;
}
