//
// Created by Martin on 2023. 05. 13..
//

#pragma once

#include <string>
#include <vector>
#include "Ciff.h"

class Caff {
private:
    std::string fileName;
    bool headerRead = false;
    bool creditsRead = false;
    bool animationRead = false;
    int numberOfAnimations = 0;

    int year = 0;
    int month = 0;
    int day = 0;
    int hour = 0;
    int minute = 0;

    std::string creator;

    std::vector<int> durations;
    std::vector<Ciff> ciffImages;

    void readFileHeader(std::ifstream &file);

    void readHeader(std::ifstream &file, int length);
    void readCredits(std::ifstream &file, int length);
    void readAnimation(std::ifstream &file);
public:
    explicit Caff(const std::string &filePath);

    void convert();
};

