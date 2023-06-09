//
// Created by Martin on 2023. 05. 18..
//

#pragma once

#include <fstream>

class Ciff {
private:
    std::string fileName;
    int width = 0;
    int height = 0;

    int contentSize = 0;
    std::string caption;
    std::vector<std::string> tags;

    unsigned char *content;

    void readHeader(std::ifstream &file);
    void readContent(std::ifstream &file);
public:
    explicit Ciff(std::ifstream &file, std::string fileName);
    void convert() const;
};
