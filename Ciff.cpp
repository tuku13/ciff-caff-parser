//
// Created by Martin on 2023. 05. 18..
//

#include <iostream>
#include <vector>
#include "Ciff.h"
#include "utils.h"
#include "constants.h"
#include "FileFormatException.h"

Ciff::Ciff(std::ifstream &file) {
    readHeader(file);
    readContent(file);
}

void Ciff::readHeader(std::ifstream &file) {
    std::string magic = utils::readAsString(file, MAGIC_SIZE);
    if (magic != CIFF_MAGIC) {
        throw FileFormatException("Invalid magic: " + magic);
    }

    int headerSize = utils::readAsInt(file, HEADER_LENGTH_SIZE);

    contentSize = utils::readAsInt(file, CONTENT_SIZE);
    width = utils::readAsInt(file, WIDTH_SIZE);
    height = utils::readAsInt(file, HEIGHT_SIZE);

    if (width < 0 || height < 0) {
        throw FileFormatException("Invalid dimension: width = " + std::to_string(width) + ", height = " + std::to_string(height));
    }

    int actualImageSize = width * height * 3;
    if (actualImageSize != contentSize) {
        throw FileFormatException(
                "Invalid image size: " + std::to_string(actualImageSize) + " != " + std::to_string(contentSize));
    }

    int captionAndTagsLength = headerSize - MAGIC_SIZE - HEADER_LENGTH_SIZE - CONTENT_SIZE - WIDTH_SIZE - HEIGHT_SIZE;
    if (captionAndTagsLength <= 0) {
        throw FileFormatException(
                "Caption's and tags' length is a non-positive number: " + std::to_string(captionAndTagsLength));
    }

    char captionAndTagsBytes[captionAndTagsLength];
    file.read(captionAndTagsBytes, captionAndTagsLength);

    int whiteSpaceCount = 0;
    int endOfCaption = -1;
    for (int i = 0; i <= captionAndTagsLength - 1; i++) {
        if (captionAndTagsBytes[i] == '\n') {
            whiteSpaceCount++;
            if (whiteSpaceCount == 1) {
                endOfCaption = i;
            }
        }
    }

    if (endOfCaption == -1 || whiteSpaceCount == 0) {
        throw FileFormatException("The caption doesn't have proper ending '\\n' character");
    }

    if (whiteSpaceCount > 1) {
        throw FileFormatException("The caption contains more than one '\\n' characters");
    }

    char captionBytes[endOfCaption + 1];
    memcpy(captionBytes, captionAndTagsBytes, endOfCaption);
    captionBytes[endOfCaption] = '\0';
    caption = captionBytes;
    std::cout << "caption: " << caption << std::endl;

    int tagsLength = captionAndTagsLength - endOfCaption + 1;
    char tagsBytes[tagsLength];
    memcpy(tagsBytes, captionAndTagsBytes + endOfCaption + 1, tagsLength);

    if (tagsBytes[tagsLength - 1] != '\0') {
        throw FileFormatException("The tags block don't end with '\\0' character");
    }

    std::string tagSegment;
    for (char c: tagsBytes) {
        if (c == '\0') {
            tagSegment += '\0';
            tags.push_back(tagSegment);
            tagSegment.clear();
        } else {
            tagSegment += c;
        }
    }

    std::cout << "tags:" << std::endl;
    for (const std::string &tag: tags) {
        std::cout << "\t- " << tag << std::endl;
    }
}

void Ciff::readContent(std::ifstream &file) {
    for (int i = 0; i <= contentSize / 3 - 1; i++) {
        int r = utils::readAsInt(file, 1);
        int g = utils::readAsInt(file, 1);
        int b = utils::readAsInt(file, 1);

        pixels.emplace_back(r, g, b);
    }
}
