//
// Created by Martin on 2023. 05. 18..
//

#pragma once

#include <fstream>
#include "Pixel.h"

class Ciff {
private:
    int width = 0;
    int height = 0;

    int contentSize = 0;
    std::string caption;
    std::vector<std::string> tags;

    std::vector<Pixel> pixels;
    uint8_t *content;

    void readHeader(std::ifstream &file);
    void readContent(std::ifstream &file);
public:
    explicit Ciff(std::ifstream &file);
    void convert(const std::string& outputFileName) const;
};
