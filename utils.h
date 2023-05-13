//
// Created by Martin on 2023. 05. 13..
//

#ifndef CIFF_CAFF_PARSER_UTILS_H
#define CIFF_CAFF_PARSER_UTILS_H

#include <fstream>

#define HEADER_TYPE_HEADER 1
#define HEADER_TYPE_CREDITS 2
#define HEADER_TYPE_ANIMATION 3

#define HEADER_LENGTH_SIZE 8
#define MAGIC_SIZE 4
#define NUMBER_OF_ANIMATIONS_SIZE 8

#define CAFF_MAGIC "CAFF"

namespace utils {
    int covertToInt(const char* data) {
        int value = static_cast<int>(static_cast<unsigned char>(*data));
        return value;
    }

    int readAsInt(std::ifstream &file, const int bytes) {
        char data[bytes];
        file.read(data, bytes);
        return utils::covertToInt(data);
    }
}

#endif //CIFF_CAFF_PARSER_UTILS_H
