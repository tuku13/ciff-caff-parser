//
// Created by Martin on 2023. 05. 13..
//

#include <fstream>
#include <iostream>
#include "Caff.h"
#include "FileFormatException.h"
#include "utils.h"

Caff::Caff(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        throw FileFormatException(fileName + " not found.");
    }

    bool fileProcessed = false;
    while (!fileProcessed) {
        try {
            readFileHeader(file);
        } catch (FileFormatException &exception) {
            file.close();
            throw FileFormatException(exception.what());
        }
        fileProcessed = true;
    }

    file.close();
}

void Caff::readFileHeader(std::ifstream &file) {
    int headerType = utils::readAsInt(file, 1);

    switch (headerType) {
        case HEADER_TYPE_HEADER:
            std::cout << "HEADER" << std::endl;
            readHeader(file);
            break;
        case HEADER_TYPE_CREDITS:
            std::cout << "CREDITS" << std::endl;
            readCredits(file);
            break;
        case HEADER_TYPE_ANIMATION:
            std::cout << "ANIMATION" << std::endl;
            readAnimation(file);
            break;
        default:
            throw FileFormatException(&"Unknown header type"[headerType]);
    }
    file.close();

    if (!headerRead || !creditsRead || !animationRead) {

    }
}

void Caff::readHeader(std::ifstream &file) {
    int length = utils::readAsInt(file, HEADER_LENGTH_SIZE);
    char data[length];
    file.read(data, length);
    processHeader(data, length);
    headerRead = true;
}

void Caff::readCredits(std::ifstream &file) {
    if (!headerRead) {
        throw FileFormatException("The file should start with CAFF header.");
    }
    creditsRead = true;
}

void Caff::readAnimation(std::ifstream &file) {
    if (!headerRead) {
        throw FileFormatException("The file should start with CAFF header.");
    }
    animationRead = true;
}

void Caff::convert() {
    std::cout << "convert" << std::endl;
}

void Caff::processHeader(const char *headerData, int headerLength) {
    char magicBytes[MAGIC_SIZE + 1];
    memcpy(magicBytes, headerData, MAGIC_SIZE);
    magicBytes[MAGIC_SIZE] = '\0';
    std::string magic = magicBytes;

    if (magic != CAFF_MAGIC) {
        throw FileFormatException("Invalid magic: " + magic);
    }

    char lengthBytes[HEADER_LENGTH_SIZE];
    memcpy(lengthBytes, headerData + MAGIC_SIZE, HEADER_LENGTH_SIZE);
    int length = utils::covertToInt(lengthBytes);

    if (length != headerLength) {
        throw FileFormatException(
                "The provided (" + std::to_string(length) + ") and the real length (" + std::to_string(headerLength) +
                ") if the header are different.");
    }

    char numberOfAnimationBytes[NUMBER_OF_ANIMATIONS_SIZE];
    memcpy(numberOfAnimationBytes, headerData + MAGIC_SIZE + HEADER_LENGTH_SIZE, NUMBER_OF_ANIMATIONS_SIZE);
    numberOfAnimations = utils::covertToInt(numberOfAnimationBytes);
}
