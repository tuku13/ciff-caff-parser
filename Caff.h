//
// Created by Martin on 2023. 05. 13..
//

#ifndef CIFF_CAFF_PARSER_CAFF_H
#define CIFF_CAFF_PARSER_CAFF_H

#include <string>

class Caff {
private:
    bool headerRead = false;
    bool creditsRead = false;
    bool animationRead = false;
    int numberOfAnimations = 0;

    void readFileHeader(std::ifstream &file);

    void readHeader(std::ifstream &file);
    void processHeader(const char* headerData, int headerLength);

    void readCredits(std::ifstream &file);

    void readAnimation(std::ifstream &file);
public:
    explicit Caff(const std::string &filePath);


    void convert();
};


#endif //CIFF_CAFF_PARSER_CAFF_H
