//
// Created by Martin on 2023. 05. 13..
//

#include <fstream>
#include <iostream>
#include "Caff.h"
#include "FileFormatException.h"
#include "constants.h"
#include "utils.h"
#include <cstring>

Caff::Caff(const std::string &fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        throw FileFormatException(fileName + " not found.");
    }

//    bool fileProcessed = false;
    int processedHeaders = 0;
    while (processedHeaders < 3) {
        try {
            readFileHeader(file);
        } catch (FileFormatException &exception) {
            file.close();
            throw FileFormatException(exception.what());
        }
        processedHeaders++;
//        fileProcessed = true;
    }

    file.close();
}

void Caff::readFileHeader(std::ifstream &file) {
    int headerType = utils::readAsInt(file, 1);
    int length = utils::readAsInt(file, HEADER_LENGTH_SIZE);

    switch (headerType) {
        case HEADER_TYPE_HEADER:
            std::cout << "HEADER" << std::endl;
            readHeader(file, length);
            break;
        case HEADER_TYPE_CREDITS:
            std::cout << "CREDITS" << std::endl;
            readCredits(file, length);
            break;
        case HEADER_TYPE_ANIMATION:
            std::cout << "ANIMATION" << std::endl;
            readAnimation(file, length);
            break;
        default:
            throw FileFormatException("Unknown header type: " + std::to_string(headerType));
    }

    if (!headerRead || !creditsRead || !animationRead) {

    }
}

void Caff::readHeader(std::ifstream &file, int length) {
    char data[length];
    file.read(data, length);

    char magicBytes[MAGIC_SIZE + 1];
    memcpy(magicBytes, data, MAGIC_SIZE);
    magicBytes[MAGIC_SIZE] = '\0';
    std::string magic = magicBytes;

    if (magic != CAFF_MAGIC) {
        throw FileFormatException("Invalid magic: " + magic);
    }

    char sizeBytes[HEADER_LENGTH_SIZE];
    memcpy(sizeBytes, data + MAGIC_SIZE, HEADER_LENGTH_SIZE);
    int size = utils::covertToInt(sizeBytes);

    if (size != length) {
        throw FileFormatException(
                "The provided (" + std::to_string(size) + ") and the real size (" + std::to_string(length) +
                ") if the header are different.");
    }

    char numberOfAnimationBytes[NUMBER_OF_ANIMATIONS_SIZE];
    memcpy(numberOfAnimationBytes, data + MAGIC_SIZE + HEADER_LENGTH_SIZE, NUMBER_OF_ANIMATIONS_SIZE);
    numberOfAnimations = utils::covertToInt(numberOfAnimationBytes);

    headerRead = true;
}

void Caff::readCredits(std::ifstream &file, int length) {
    if (!headerRead) {
        throw FileFormatException("The file should start with CAFF header.");
    }

    year = utils::readAsInt(file, YEAR_SIZE);
    month = utils::readAsInt(file, MONTH_SIZE);
    day = utils::readAsInt(file, DAY_SIZE);
    hour = utils::readAsInt(file, HOUR_SIZE);
    minute = utils::readAsInt(file, MINUTE_SIZE);

    int creatorLength = utils::readAsInt(file, CREATOR_LENGTH_SIZE);
    if (DATE_SIZE + CREATOR_LENGTH_SIZE + creatorLength != length) {
        throw FileFormatException("The creator field exceeds the header's length (" + std::to_string(creatorLength) + " > " + std::to_string(length)+ ").");
    }
    creator = utils::readAsString(file, creatorLength);

    creditsRead = true;
}

void Caff::readAnimation(std::ifstream &file, int length) {
    if (!headerRead) {
        throw FileFormatException("The file should start with CAFF header.");
    }

    int duration = utils::readAsInt(file, DURATION_SIZE);
    durations.push_back(duration);

    animationRead = true;
}

void Caff::convert() {
    std::cout << "convert" << std::endl;
}
